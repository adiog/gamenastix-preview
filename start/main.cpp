// This file is a part of Treadmill project.
// Copyright 2018 Disco WTMH S.A.

#include <Protocol.h>
#include <udpbox.h>
#include <iostream>
#include <GL/glut.h>
#include <component/Scene.h>
#include <deepModel/Model.h>
#include <deepModel/Treadmill.h>
#include <opengl/ContextMenu.h>
#include <opengl/Display.h>
#include <opengl/KeyboardController.h>
#include <opengl/MouseController.h>


template <typename OnLoadCallback>
int main_opengl(int argc, char** argv, OnLoadCallback onLoadCallback)
{
    const int WIN_WIDTH = 800;
    const int WIN_HEIGHT = 800;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Gamenastix Preview (C) DiscoWTMH");

    OrbitCamera::resetCamera();
    Display::intialization();
    glutReshapeFunc(Display::rashape);
    glutDisplayFunc(Display::display);
    glutIdleFunc(Display::display);
    glutMotionFunc(MouseController::pressedMouseCallback);
    glutMouseFunc(MouseController::mouseCallback);
    glutPassiveMotionFunc(MouseController::passiveMouseCallback);
    ContextMenu::createContextMenu();
    glutKeyboardFunc(KeyboardController::keyboardCallback);
    Display::redisplay();
    onLoadCallback();
    glutMainLoop();
    return 0;
}


model::Layout getLayout(biomodel::deepModel::Model& model)
{
    model::Layout layout;

    static const std::unordered_map<bio::Segment, Part> mapping = {
        {bio::Segment::UpperLegLeft, Part::LEFT_LEG_UPPER},
        {bio::Segment::LowerLegLeft, Part::LEFT_LEG_LOWER},
        {bio::Segment::UpperLegRight, Part::RIGHT_LEG_UPPER},
        {bio::Segment::LowerLegRight, Part::RIGHT_LEG_LOWER}};

    for (auto& mappingEntry : mapping)
    {
        auto params = model.get(mappingEntry.second);
        if ((params[0] == 0) && (params[1] == 0) && (params[2] == 0))
        {
            layout.segmentLayout[mappingEntry.first] = glm::vec3(0, 0, 0);
        }
        else
        {
            layout.segmentLayout[mappingEntry.first] = glm::vec3(params[0], params[1], 180-params[2]);
        }
    }

    layout.segmentLayout[bio::Segment::FootLeft] = {0, 90, 0};
    layout.segmentLayout[bio::Segment::FootRight] = {0, 90, 0};

    return layout;
}

int main(int argc, char** argv)
{
    biomodel::deepModel::Model model = biomodel::deepModel::Treadmill().getModel();
    openGLContext.scene.apply(getLayout(model));

    udpbox::Server server(1234);
    server.setOnDatagramCallback([&](udpbox::Datagram&& datagram) {
        Message message = datagram.payload;
        model.update(message);
        openGLContext.scene.apply(getLayout(model));
    });

    main_opengl(argc, argv, [&server]() {
        server.start();
    });

    return 0;
}
