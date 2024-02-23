// #include "driver/i2s.h"
// #include "esp_log.h"
// #include "esp_err.h"
// #define I2S_SAMPLE_RATE     (16000)
// #define I2S_CHANNELS        (1)
// #include <inttypes.h>
// #include <stdio.h> 
// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "esp_log.h"
// #include "esp_wifi.h"
// #include "esp_event.h"
// #include "esp_netif.h"
// #include "esp_system.h"
// #include "nvs_flash.h"
// #include "lwip/sockets.h"
// #include "lwip/netdb.h"
// #include "lwip/ip.h"
// #include "lwip/tcp.h"
// #include "lwip/ip4_addr.h"
// #include "lwip/ip4.h"
// #include "lwip/altcp_tcp.h"
// #include "lwip/raw.h"
// #include "lwip/ip_addr.h"
// #include "lwip/ip.h"
// #include "lwip/tcp.h"
// #include <fcntl.h>
// #include <errno.h>
// #include <stdio.h>
// #include <string.h>
// #include "esp_system.h"
// #include "esp_wifi.h"
// #include "esp_event.h"
// #include "esp_log.h"
// #include "esp_netif.h"
// #include "freertos/event_groups.h"
// //#include "protocol_examples_common.h"
// #include "esp_transport_ws.h"
// #include "esp_http_client.h"
// #include "stdio.h"
// #include "driver/i2c.h"
// #include "driver/gpio.h"
// #include "esp_event.h"
// #include "esp_log.h"

// #define WIFI_CONNECTED_BIT BIT0

// char send_buffer[300];
// int send_len = 0;

// EventGroupHandle_t s_wifi_event_group;

// #define WS_ENDPOINT "ws://10.2.30.1:8888"

// static const char *TAG = "Socket_Client";

// #define SERVER_IP           "10.2.30.202"
// #define SERVER_PORT         5005

// int16_t audio_buffer[1024];

// static void event_handler(void* arg, esp_event_base_t event_base,
//                                 int32_t event_id, void* event_data)
// {
//     if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
//         printf("Connection to the access point failed\n");
//         esp_wifi_connect();
//     } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
//         xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
//     }
// }

// // void udp_sender_task(void *pvParameters) {
// //     struct sockaddr_in dest_addr;
// //     int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
// //     if (sock < 0) {
// //         ESP_LOGE(TAG, "Unable to create socket: errno %d", errno);
// //         vTaskDelete(NULL);
// //         return;
// //     }

// //     memset(&dest_addr, 0, sizeof(dest_addr));
// //     dest_addr.sin_family = AF_INET;
// //     dest_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
// //     dest_addr.sin_port = htons(SERVER_PORT);

// //     char *data = "sam";
// //     ssize_t sent_bytes;

// //     while (1) {
// //         sent_bytes = sendto(sock, &audio_buffer, 1024, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
// //         if (sent_bytes < 0) {
// //             ESP_LOGE(TAG, "Failed to send UDP data: errno %d", errno);
// //         } else {
// //             ESP_LOGI(TAG, "Sent %d bytes of UDP data", (int)sent_bytes);
// //         }
// //     }
// // }





// void initialize_wifi() {

//     s_wifi_event_group = xEventGroupCreate();

//     ESP_ERROR_CHECK(esp_netif_init());
//     ESP_ERROR_CHECK(esp_event_loop_create_default());
//     esp_netif_create_default_wifi_sta();
//     wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
//     ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
//     ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );

//     esp_event_handler_instance_t instance_any_id;
//     esp_event_handler_instance_t instance_got_ip;
//     ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
//                                                         ESP_EVENT_ANY_ID,
//                                                         &event_handler,
//                                                         NULL,
//                                                         &instance_any_id));
//     ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
//                                                         IP_EVENT_STA_GOT_IP,
//                                                         &event_handler,
//                                                         NULL,
//                                                         &instance_got_ip));

//     wifi_config_t wifi_config = {
//         .sta = {
//             .ssid = "SCLERA",
//             .password = "Password123"
//         }
//     };                                                    

//     ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
//     ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));

//     ESP_ERROR_CHECK( esp_wifi_start());
    

//     esp_wifi_connect();
    
//     printf("Before waiting for WiFi connected event\n");

//     TickType_t xTicksToWait = pdMS_TO_TICKS(10000);  // Adjust the timeout as needed
//     EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
//             WIFI_CONNECTED_BIT,
//             pdFALSE,
//             pdFALSE,
//             xTicksToWait);

//     printf("After waiting for WiFi connected event\n");

//     if(bits & WIFI_CONNECTED_BIT){
//         printf("Connected to AP.!!!!!!!!!");

//         ESP_LOGI("WIFI_INIT","CONNECTED BRO!!!");
//         // ESP_ERROR_CHECK( esp_wifi_set_channel(3, WIFI_SECOND_CHAN_NONE));
//     }else{
//         printf("Failed to connect!!!!");
//     }
// }

// void ws_client_task(void *pvParameters) {
    

//     // esp_transport_ws_send_raw
//     // esp_http_client_config_t config = {
//     //     .url = WS_ENDPOINT,
//     //     .host = "10.2.30.1",
//     //     .port = 8888,
//     //     .transport_type = transport
//     // };
    
//     // esp_http_client_handle_t client = esp_http_client_init(&config);
//     // if (client == NULL) {
//     //     ESP_LOGE(TAG, "Failed to initialize HTTP client");
//     //     esp_transport_destroy(transport);
//     //     vTaskDelete(NULL);
//     //     return;
//     // }

//     while (1) {
//         // // Send audio data from audio_buffer
//         // esp_http_client_set_post_field(client, (char *)audio_buffer, sizeof(audio_buffer));
//         // esp_err_t err = esp_http_client_perform(client);
//         // if (err == ESP_OK) {
//         //     ESP_LOGI(TAG, "Data sent successfully");
//         // } else {
//         //     ESP_LOGE(TAG, "Failed to send data");
//         // }
//         printf("HI");
//         vTaskDelay(1);
//     }

//     // esp_http_client_cleanup(client);
//     // esp_transport_destroy(transport);
//     vTaskDelete(NULL);
// }



// void app_main(void) {

//         ESP_LOGI(TAG,"this is the imp");
//     //syn_queue = xQueueCreate(10, BUF_SIZE);
//        // Initialize NVS
//     esp_err_t ret = nvs_flash_init();
//     if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
//         ESP_ERROR_CHECK(nvs_flash_erase());
//         ret = nvs_flash_init();
//     }
//     ESP_ERROR_CHECK(ret);

//      initialize_wifi();


//     //Configure I²S peripheral
//     i2s_config_t i2s_config = {
//         .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
//         .sample_rate = 44100,
//         .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
//         .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // Mono mode for INMP441
//         .communication_format = I2S_COMM_FORMAT_STAND_I2S,
//         .intr_alloc_flags = 0,    // Interrupt level 1
//         .dma_buf_count = 10,
//         .dma_buf_len = 1024,
//         .use_apll = false
//     };

//       i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    
//     i2s_pin_config_t pin_config = {
//         .bck_io_num = GPIO_NUM_13,
//         .ws_io_num = GPIO_NUM_11,
//         .data_out_num = I2S_PIN_NO_CHANGE,
//         .data_in_num = GPIO_NUM_12,
//     };


  
//     i2s_set_pin(I2S_NUM_0, &pin_config);

//     // i2s_start(I2S_NUM_0);

//     size_t bytesIn = 0;

//     // xTaskCreate(ws_client_task, "ws_client_task", 4096, NULL, 5, NULL);
//    // Read and process audio data from I²S peripheral

//    // xTaskCreate(udp_sender_task, "udp_sender_task", configMINIMAL_STACK_SIZE * 4, NULL, 5, NULL);

//     // Start WebSocket client task
//     esp_transport_handle_t transport = esp_transport_ws_init(WS_ENDPOINT);
//     if (!transport) {
//         ESP_LOGE(TAG, "Failed to initialize WebSocket transport");
//         vTaskDelete(NULL);
//         return;
//     }

//     int res = esp_transport_connect(transport,"10.2.30.1",8888,0);
//     if(res < 0){
//         ESP_LOGE(TAG,"Cant connect");
//     }
//     //xTaskCreate(ws_client_task, "ws_client_task", 4096, NULL, 5, NULL);

//     while (1) {
//         //size_t bytes_read = 100;
//         // Read audio data from I²S peripheral into buffer

//         esp_err_t result  = i2s_read(I2S_NUM_0, &audio_buffer,1024, &bytesIn, portMAX_DELAY);

//         if(result == ESP_OK){
//             ESP_LOGI("audio","getting the data");
//         }
//         // Process audio data
//         //process_audio_data(audio_buffer, bytes_read);
//     }

// //     // Free allocated memory
// //     free(audio_buffer);
// }


/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <stdio.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/event_groups.h"
#include "driver/i2s.h"
#include "esp_websocket_client.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_event.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_netif.h"

#define WIFI_CONNECTED_BIT BIT0

char send_buffer[300];
int send_len = 0;
int16_t audio_buffer[4410];


EventGroupHandle_t s_wifi_event_group;


static void event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        printf("Connection to the access point failed\n");
        esp_wifi_connect();
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    }
}


static const char *TAG = "websocket";

void initialize_wifi() {

    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );

    esp_event_handler_instance_t instance_any_id;
    esp_event_handler_instance_t instance_got_ip;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
                                                        ESP_EVENT_ANY_ID,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_any_id));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
                                                        IP_EVENT_STA_GOT_IP,
                                                        &event_handler,
                                                        NULL,
                                                        &instance_got_ip));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "SCLERA",
            .password = "Password123"
        }
    };                                                    

    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));

    ESP_ERROR_CHECK( esp_wifi_start());
    

    esp_wifi_connect();
    
    printf("Before waiting for WiFi connected event\n");

    TickType_t xTicksToWait = pdMS_TO_TICKS(10000);  // Adjust the timeout as needed
    EventBits_t bits = xEventGroupWaitBits(s_wifi_event_group,
            WIFI_CONNECTED_BIT,
            pdFALSE,
            pdFALSE,
            xTicksToWait);

    printf("After waiting for WiFi connected event\n");

    if(bits & WIFI_CONNECTED_BIT){
        printf("Connected to AP.!!!!!!!!!");

        ESP_LOGI("WIFI_INIT","CONNECTED BRO!!!");
        // ESP_ERROR_CHECK( esp_wifi_set_channel(3, WIFI_SECOND_CHAN_NONE));
    }else{
        printf("Failed to connect!!!!");
    }
}

void ws_client_task(void *pvParameters) {
    

    // esp_transport_ws_send_raw
    // esp_http_client_config_t config = {
    //     .url = WS_ENDPOINT,
    //     .host = "10.2.30.1",
    //     .port = 8888,
    //     .transport_type = transport
    // };
    
    // esp_http_client_handle_t client = esp_http_client_init(&config);
    // if (client == NULL) {
    //     ESP_LOGE(TAG, "Failed to initialize HTTP client");
    //     esp_transport_destroy(transport);
    //     vTaskDelete(NULL);
    //     return;
    // }

    while (1) {
        // // Send audio data from audio_buffer
        // esp_http_client_set_post_field(client, (char *)audio_buffer, sizeof(audio_buffer));
        // esp_err_t err = esp_http_client_perform(client);
        // if (err == ESP_OK) {
        //     ESP_LOGI(TAG, "Data sent successfully");
        // } else {
        //     ESP_LOGE(TAG, "Failed to send data");
        // }
        printf("HI");
        vTaskDelay(1);
    }

    // esp_http_client_cleanup(client);
    // esp_transport_destroy(transport);
    vTaskDelete(NULL);
}

static void log_error_if_nonzero(const char *message, int error_code)
{
    if (error_code != 0) {
        ESP_LOGE(TAG, "Last error %s: 0x%x", message, error_code);
    }
}

static void websocket_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_websocket_event_data_t *data = (esp_websocket_event_data_t *)event_data;
    switch (event_id) {
    case WEBSOCKET_EVENT_CONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_CONNECTED");
        break;
    case WEBSOCKET_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DISCONNECTED");
        log_error_if_nonzero("HTTP status code",  data->error_handle.esp_ws_handshake_status_code);
        if (data->error_handle.error_type == WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", data->error_handle.esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", data->error_handle.esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  data->error_handle.esp_transport_sock_errno);
        }
        break;
    case WEBSOCKET_EVENT_DATA:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_DATA");
        ESP_LOGI(TAG, "Received opcode=%d", data->op_code);
        if (data->op_code == 0x08 && data->data_len == 2) {
            ESP_LOGW(TAG, "Received closed message with code=%d", 256 * data->data_ptr[0] + data->data_ptr[1]);
        } else {
            ESP_LOGW(TAG, "Received=%.*s", data->data_len, (char *)data->data_ptr);
        }

        // If received data contains json structure it succeed to parse
        ESP_LOGW(TAG, "Total payload length=%d, data_len=%d, current payload offset=%d\r\n", data->payload_len, data->data_len, data->payload_offset);

        break;
    case WEBSOCKET_EVENT_ERROR:
        ESP_LOGI(TAG, "WEBSOCKET_EVENT_ERROR");
        log_error_if_nonzero("HTTP status code",  data->error_handle.esp_ws_handshake_status_code);
        if (data->error_handle.error_type == WEBSOCKET_ERROR_TYPE_TCP_TRANSPORT) {
            log_error_if_nonzero("reported from esp-tls", data->error_handle.esp_tls_last_esp_err);
            log_error_if_nonzero("reported from tls stack", data->error_handle.esp_tls_stack_err);
            log_error_if_nonzero("captured as transport's socket errno",  data->error_handle.esp_transport_sock_errno);
        }
        break;
    }
}


static void websocket_app_start(void)
{
    esp_websocket_client_config_t websocket_cfg = {};

    websocket_cfg.uri = "ws://10.2.30.202:8888";

    ESP_LOGI(TAG, "Connecting to %s...", websocket_cfg.uri);

    esp_websocket_client_handle_t client = esp_websocket_client_init(&websocket_cfg);
    // This call demonstrates adding another header; it's called to increase code coverage
    esp_websocket_client_append_header(client, "HeaderNewKey", "value");

    esp_websocket_register_events(client, WEBSOCKET_EVENT_ANY, websocket_event_handler, (void *)client);

    esp_websocket_client_start(client);
    char data[32];
    int i = 0;
    while (1) {
        if (esp_websocket_client_is_connected(client)) {
            int len = sprintf(data, "hello %04d", i++);
            ESP_LOGI(TAG, "Sending %s", data);
            esp_websocket_client_send_bin(client,&audio_buffer,4410,portMAX_DELAY);
           // esp_websocket_client_send_text(client, data, len, portMAX_DELAY);
        }
        vTaskDelay(1);
    }

    ESP_LOGI(TAG, "Sending fragmented message");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    memset(data, 'a', sizeof(data));
    esp_websocket_client_send_text_partial(client, data, sizeof(data), portMAX_DELAY);
    memset(data, 'b', sizeof(data));
    esp_websocket_client_send_cont_msg(client, data, sizeof(data), portMAX_DELAY);
    esp_websocket_client_send_fin(client, portMAX_DELAY);

    esp_websocket_client_destroy(client);
}

int app_main(void)
{

    ESP_LOGI(TAG, "[APP] Startup..");
    ESP_LOGI(TAG, "[APP] Free memory: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "[APP] IDF version: %s", esp_get_idf_version());
    esp_log_level_set("*", ESP_LOG_INFO);
    esp_log_level_set("websocket_client", ESP_LOG_DEBUG);
    esp_log_level_set("transport_ws", ESP_LOG_DEBUG);
    esp_log_level_set("trans_tcp", ESP_LOG_DEBUG);

    ESP_ERROR_CHECK(nvs_flash_init());
    // ESP_ERROR_CHECK(esp_netif_init());
    // ESP_ERROR_CHECK(esp_event_loop_create_default());

    /* This helper function configures Wi-Fi or Ethernet, as selected in menuconfig.
     * Read "Establishing Wi-Fi or Ethernet Connection" section in
     * examples/protocols/README.md for more information about this function.
     */
    initialize_wifi();


    //i2c
        //Configure I²S peripheral
    // i2s_config_t i2s_config = {
    //     .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    //     .sample_rate = 44100,
    //     .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    //     .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // Mono mode for INMP441
    //     .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    //     .intr_alloc_flags = 0,    // Interrupt level 1
    //     .dma_buf_count = 10,
    //     .dma_buf_len = 1024,
    //     .use_apll = false
    // };

    i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // Mono mode for INMP441
    .communication_format = I2S_COMM_FORMAT_STAND_I2S,
    .intr_alloc_flags = 0,    // Interrupt level 1
    .dma_buf_count = 10,
    .dma_buf_len = 128,
    .use_apll = false
};

      i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
    
    i2s_pin_config_t pin_config = {
        .bck_io_num = GPIO_NUM_13,
        .ws_io_num = GPIO_NUM_11,
        .data_out_num = I2S_PIN_NO_CHANGE,
        .data_in_num = GPIO_NUM_12,
    };


  
    i2s_set_pin(I2S_NUM_0, &pin_config);
   // i2s_set_clk(I2S_NUM_0, 44100, I2S_BITS_PER_SAMPLE_16BIT, I2S_CHANNEL_MONO);


    i2s_start(I2S_NUM_0);

    size_t bytesIn = 0;
    
    xTaskCreate(websocket_app_start, "web socket app start", 4096, NULL, 5, NULL);


    while (1) {
        //size_t bytes_read = 100;
        // Read audio data from I²S peripheral into buffer

        esp_err_t result  = i2s_read(I2S_NUM_0, &audio_buffer,1024, &bytesIn, portMAX_DELAY);

        if(result == ESP_OK){
            ESP_LOGI("audio","getting the data");
        }
        // Process audio data
        //process_audio_data(audio_buffer, bytes_read);
    }
    return 0;
}