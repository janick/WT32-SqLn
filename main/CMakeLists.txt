file(GLOB_RECURSE UI_FILES "ui/*.c")

idf_component_register(SRCS "main.cpp" ${UI_FILES}
                INCLUDE_DIRS "." "devices" "helpers" "ui"
				REQUIRES LovyanGFX lvgl
				app_update esp_https_ota esp_event esp_timer spi_flash esp_wifi esp_partition
				esp_hw_support
                                # Embed the server root certificate into the final binary
                                EMBED_TXTFILES ${project_dir}/server_certs/ca_cert.pem
				)
