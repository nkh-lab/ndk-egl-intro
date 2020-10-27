#include <android_native_app_glue.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

static void engine_handle_cmd(struct android_app* app, int32_t cmd);
static void egl_intro(struct android_app* app);

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state)
{
    state->onAppCmd = engine_handle_cmd;

    int events;
    struct android_poll_source* source;

    while (true)
    {
        while (ALooper_pollAll(0, nullptr, &events, (void**)&source) >= 0)
        {
            if (source != nullptr)
            {
                source->process(state, source);
            }
        }
    }
}

/**
 * Process the next main command.
 */
static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
    switch (cmd)
    {
    case APP_CMD_SAVE_STATE:
        break;
    case APP_CMD_INIT_WINDOW:
        egl_intro(app);
        break;
    case APP_CMD_TERM_WINDOW:
        break;
    case APP_CMD_GAINED_FOCUS:
        break;
    case APP_CMD_LOST_FOCUS:
        break;
    default:
        break;
    }
}

/**
 * EGL example as is from https://www.khronos.org/registry/EGL/sdk/docs/man/html/eglIntro.xhtml
 */
// clang-format off
static EGLint const attribute_list[] = {
        EGL_RED_SIZE, 1,
        EGL_GREEN_SIZE, 1,
        EGL_BLUE_SIZE, 1,
        EGL_NONE
};
static void egl_intro(struct android_app* app)
{
    EGLDisplay display;
    EGLConfig config;
    EGLContext context;
    EGLSurface surface;
    NativeWindowType native_window;
    EGLint num_config;

    /* get an EGL display connection */
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    /* initialize the EGL display connection */
    eglInitialize(display, NULL, NULL);

    /* get an appropriate EGL frame buffer configuration */
    eglChooseConfig(display, attribute_list, &config, 1, &num_config);

    /* create an EGL rendering context */
    context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);

    /* create a native window */
    native_window = app->window; // createNativeWindow();

    /* create an EGL window surface */
    surface = eglCreateWindowSurface(display, config, native_window, NULL);

    /* connect the context to the surface */
    eglMakeCurrent(display, surface, surface, context);

    /* clear the color buffer */
    glClearColor(1.0, 1.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

    eglSwapBuffers(display, surface);
}
// clang-format on
