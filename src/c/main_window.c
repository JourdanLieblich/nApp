#include <pebble.h>

#include "src/c/main_window.h"


// Using a text layer for now to specify the background and sidebar, 
// I'm thinking there's a more specific way to do that

static Window *window;
static TextLayer *background_layer;
static TextLayer *sidebar_layer;
static GBitmap *large_zzz;
static GBitmap *small_zzz;
static GBitmap *stopwatch;
static BitmapLayer *large_zzz_layer;
static BitmapLayer *small_zzz_layer;
static BitmapLayer *stopwatch_layer;


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(background_layer, "Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(background_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(background_layer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

void setup_background_layer(Window *window) {
  
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);
  
  background_layer = text_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
  text_layer_set_font(background_layer, fonts_get_system_font(FONT_KEY_LECO_42_NUMBERS));
  text_layer_set_background_color(background_layer, GColorBlack);
  layer_add_child(window_layer, text_layer_get_layer(background_layer));
}

void setup_sidebar_layer(Window *window) {
  Layer *window_layer = window_get_root_layer(window);

  GRect bounds = layer_get_bounds(window_layer);
  
  // Sidebar Layer setup
  sidebar_layer = text_layer_create(GRect(100, 0, 44, bounds.size.h));
  text_layer_set_background_color(sidebar_layer, GColorWhite);
  layer_add_child(window_layer, text_layer_get_layer(sidebar_layer));
  
  // Large ZZZ image setup
  large_zzz = gbitmap_create_with_resource(RESOURCE_ID_ZZZ_LARGE);
  large_zzz_layer = bitmap_layer_create(GRect(102, 0, 41, 55));
  bitmap_layer_set_compositing_mode(large_zzz_layer, GCompOpSet);
  bitmap_layer_set_bitmap(large_zzz_layer, large_zzz);
  layer_add_child(window_layer, bitmap_layer_get_layer(large_zzz_layer));
  
  // Small ZZZ image setup
  small_zzz = gbitmap_create_with_resource(RESOURCE_ID_ZZZ_SMALL);
  small_zzz_layer = bitmap_layer_create(GRect(108, 123, 30, 40));
  bitmap_layer_set_compositing_mode(small_zzz_layer, GCompOpSet);
  bitmap_layer_set_bitmap(small_zzz_layer, small_zzz);
  layer_add_child(window_layer, bitmap_layer_get_layer(small_zzz_layer));
  
  // Stopwatch image setup
  stopwatch = gbitmap_create_with_resource(RESOURCE_ID_STOPWATCH);
  stopwatch_layer = bitmap_layer_create(GRect(102, 65, 40, 40));
  bitmap_layer_set_compositing_mode(stopwatch_layer, GCompOpSet);
  bitmap_layer_set_bitmap(stopwatch_layer, stopwatch);
  layer_add_child(window_layer, bitmap_layer_get_layer(stopwatch_layer));
  
}

static void window_load(Window *window) {
  setup_background_layer(window);
  setup_sidebar_layer(window);
}

static void window_unload(Window *window) {
  text_layer_destroy(background_layer);
  text_layer_destroy(sidebar_layer);
  bitmap_layer_destroy(large_zzz_layer);
  bitmap_layer_destroy(small_zzz_layer);
  bitmap_layer_destroy(stopwatch_layer);
}

void main_window_create() {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

void main_window_destroy() {
  window_destroy(window);
}

Window* main_window_get_window(){
  return window;
}
