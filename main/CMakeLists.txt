idf_component_register(SRCS "main.cpp" "ui/ui.c" "ui/ui_helpers.c" "ui/screens/ui_Main_Screen.c" "ui/screens/ui_Splash_Screen.c"
                INCLUDE_DIRS "." "devices" "helpers" "ui"
				REQUIRES LovyanGFX lvgl
				app_update esp_https_ota esp_event esp_timer spi_flash esp_wifi esp_partition
				esp_hw_support
                                # Embed the server root certificate into the final binary
                                EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem
				)
