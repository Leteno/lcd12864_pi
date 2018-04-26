#include "get_weather.h"

#include <stdio.h>
#include <string.h>

void cmd(char *cmd, char* output, int max_siz);

void get_max_tmp(char* buffer, int max_size) {
    char* c = "curl \"https://free-api.heweather.com/s6/weather/forecast\?location=beijing&key=0375a2d678a245c08f83f628448d0ae8\" | jq \".HeWeather6[0].daily_forecast[0].tmp_max\"";
    cmd(c, buffer, max_size);
}

void get_min_tmp(char* buffer, int max_size) {
    char* c = "curl \"https://free-api.heweather.com/s6/weather/forecast\?location=beijing&key=0375a2d678a245c08f83f628448d0ae8\" | jq \".HeWeather6[0].daily_forecast[0].tmp_min\"";
    cmd(c, buffer, max_size);
}

void get_pm25(char* buffer, int max_size) {
    char* c = "curl \"https://free-api.heweather.com/s6/air/now\?location=beijing&key=0375a2d678a245c08f83f628448d0ae8\" | jq \".HeWeather6[0].air_now_city.pm25\"";
    cmd(c, buffer, max_size);
}

void cmd(char *cmd, char* output, int max_size) {
    FILE *fp;
    char tmp[1024];
    fp = popen(cmd, "r");
    if (fp == NULL) {
	printf("fail\n");
	return;
    }

    if (fgets(tmp, sizeof(tmp)-1, fp) != NULL) {
	printf("result: %s\n", tmp);
    }
    int i = 0;
    char *p = tmp;
    while (*p && i < max_size) {
	if (*p < '0' || *p > '9') {
	    // skip
	} else {
	    output[i++] = *p;
	}
	p++;
    }
    int end = i < max_size ? i : max_size - 1;
    for (i = end; i < max_size - 1; i++) {
	output[i] = '\0';
    }

    pclose(fp);
}
