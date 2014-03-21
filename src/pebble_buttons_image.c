#include <pebble.h>
 
Window *window;
BitmapLayer *image_layer;

void default_state() {
  bitmap_layer_set_bitmap(image_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NO_LITTER));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(image_layer));
}

void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  bitmap_layer_set_bitmap(image_layer, gbitmap_create_with_resource(RESOURCE_ID_PANDA_IDENTIFIER));
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(image_layer));
}

void other_click_handler(ClickRecognizerRef recognizer, void *context) {
  //bitmap_layer_set_bitmap(image_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NO_LITTER));
  //layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(image_layer));
  default_state();
}

void window_load(Window *window) {
  image_layer = bitmap_layer_create(GRect(0,0,144,168));
  //bitmap_layer_set_bitmap(image_layer, gbitmap_create_with_resource(RESOURCE_ID_IMAGE_NO_LITTER));
  //layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(image_layer));
  default_state();
}
 
void window_unload(Window *window) {
  bitmap_layer_destroy(image_layer);
}

void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, other_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, other_click_handler);
}
 
void init() {
  //Initialize the app elements here!
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  // You need this to actually you know actually load the freaking window.
  const bool animated = true;
  window_stack_push(window, animated);
}
 
void deinit() {
  window_destroy(window);
  bitmap_layer_destroy(image_layer);
}
 
int main(void) {
  init();
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);
  app_event_loop();
  deinit();
}
