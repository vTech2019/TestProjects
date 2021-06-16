#include "Application/application.h"

int main(){

    struct application app = { 0 };
    application_init(&app);
    application_run(&app);
    application_free(&app);
    return 0;
}
