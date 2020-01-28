

static const char* TAG_BTN  = "DISPOD_BUTTON";


// Button callback functions
void button_tap_cb(void* arg)
{
    char* pstr = (char*) arg;
    ESP_EARLY_LOGI(TAG_BTN, "tap cb (%s), heap: %d", pstr, esp_get_free_heap_size());
}

void button_press_2s_cb(void* arg)
{
    ESP_EARLY_LOGI(TAG_BTN, "press 2s, heap: %d", esp_get_free_heap_size());
}

void button_press_5s_cb(void* arg)
{
    ESP_EARLY_LOGI(TAG_BTN, "press 5s, heap: %d", esp_get_free_heap_size());
}

void button_test()
{
    ESP_EARLY_LOGI(TAG_BTN, "before btn init, heap: %d", esp_get_free_heap_size());

    button_handle_t btn_handle = iot_button_create(BUTTON_A_PIN, BUTTON_ACTIVE_LEVEL);

    iot_button_set_evt_cb(btn_handle, BUTTON_CB_PUSH, button_tap_cb, "PUSH");
    iot_button_set_evt_cb(btn_handle, BUTTON_CB_RELEASE, button_tap_cb, "RELEASE");
    iot_button_set_evt_cb(btn_handle, BUTTON_CB_TAP, button_tap_cb, "TAP");
    // iot_button_set_serial_cb(btn_handle, 2, 1000/portTICK_RATE_MS, button_tap_cb, "SERIAL");

    iot_button_add_custom_cb(btn_handle, 2, button_press_2s_cb, NULL);
    iot_button_add_custom_cb(btn_handle, 5, button_press_5s_cb, NULL);
    ESP_EARLY_LOGI(TAG_BTN, "after btn init, heap: %d\n", esp_get_free_heap_size());

    vTaskDelay(10000 / portTICK_PERIOD_MS);
    // printf("free btn: heap:%d\n", esp_get_free_heap_size());
    // iot_button_delete(btn_handle);
    // printf("after free btn: heap:%d\n", esp_get_free_heap_size());
}