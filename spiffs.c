
// load fonts from ...?
// static const char* file_fonts[3] = {"/spiffs/fonts/DotMatrix_M.fon", "/spiffs/fonts/Ubuntu.fon", "/spiffs/fonts/Grotesk24x48.fon"};




    // Initialize SPIFFS file system
#ifdef CONFIG_DISPOD_USE_SPIFFS
    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = false
    };

    ESP_LOGI(TAG, "SPIFFS: calling esp_vfs_spiffs_register()");
    ret = esp_vfs_spiffs_register(&conf);
    ESP_LOGI(TAG, "SPIFFS: esp_vfs_spiffs_register() returned");

    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG, "SPIFFS: Failed to mount or format filesystem");
        } else if (ret == ESP_ERR_NOT_FOUND) {
            ESP_LOGE(TAG, "SPIFFS: Failed to find SPIFFS partition");
        } else {
            ESP_LOGE(TAG, "SPIFFS: Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
        }
        return;
    }

    size_t total = 0, used = 0;
    ret = esp_spiffs_info(NULL, &total, &used);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "SPIFFS: Failed to get SPIFFS partition information (%s)", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG, "SPIFFS: Partition size: total: %d, used: %d", total, used);
    }

    // ESP_LOGI("INFO", "Reading file");
    // FILE* f = fopen("/spiffs/tiger.bmp", "r");
    // if (f == NULL) {
    //     ESP_LOGE("INFO", "Failed to open file for reading");
    //     return;
    // }
    // All done, unmount partition and disable SPIFFS
    // esp_vfs_spiffs_unregister(NULL);
    // ESP_LOGI(TAG, "SPIFFS unmounted");
#endif // CONFIG_DISPOD_USE_SPIFFS
