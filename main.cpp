#include "app.hpp"

int main() {
   App *app = new App();

   app->loop();

   delete app;
   return 0;
}