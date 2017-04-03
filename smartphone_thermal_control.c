#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int previous_cpu_freq_num = -1;
int battery_temp;
int cpu_temp;
int battery_capacity;
int cpu_freq;
int is_battery_health_good;
char battery_health[20];
int is_battery_charging;
char battery_status[13]
FILE *battery_temp_file;
FILE *battery_capacity_file;
FILE *cpu_temp_file;
FILE *cpu_freq_file[4];
FILE *battery_health_file;
FILE *battery_safety_file;
FILE *battery_status_file;


void cpu_freq_init() {
	system("chmod 666 /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq");
	system("chmod 666 /sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq");
	system("chmod 666 /sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq");
	system("chmod 666 /sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq");
	cpu_freq_file[0] = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq", "r+");
	if(!cpu_freq_file[0]) {
		printf("cpu_freq_file[0] open error\n");
		exit(-1);
	}
	cpu_freq_file[1] = fopen("/sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq", "r+");
	if(!cpu_freq_file[1]) {
		printf("cpu_freq_file[1] open error\n");
		exit(-1);
	}
	cpu_freq_file[2] = fopen("/sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq", "r+");
	if(!cpu_freq_file[3]) {
		printf("cpu_freq_file[2] open error\n");
		exit(-1);
	}
	cpu_freq_file[3] = fopen("/sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq", "r+");
	if(!cpu_freq_file[4]) {
		printf("cpu_freq_file[3] open error\n");
		exit(-1);
	}
	return;
}

int apply_cpu_freq(int step_diff) {

	int cpu_freq_list[11] = { 729600, 883200, 960000, 1036800, 
		1190400, 1267200, 1497600, 1574400, 
		1728000, 1958400, 2150400 };
	int previous_cpu_freq;
	int i;

	if(previous_cpu_freq_num == -1) {
		fscanf(cpu_freq_file[0], "%d", &previous_cpu_freq);
		for(i = 0;i < 11;i++) {
			if(previous_cpu_freq == cpu_freq_list[i]) {
				previous_cpu_freq_num = i;
			}
		}
	}
	
	if((previous_cpu_freq_num + step_diff) < 0 ||
		(previous_cpu_freq_num + step_diff) > 11 ||
		step_diff == 0) {
		return -1;
	}
	for(i = 0;i < 4;i++) {
		fprintf(cpu_freq_file[i], "%d", previous_cpu_freq_num + step_diff);
	}
	previous_cpu_freq_num += step_diff;
	return 0;
}
	
int main() {

	int i;
	int battery_temp_change_timeout;
	int battery_temp_time;

	system("su");
	cpu_freq_init();
	battery_temp_file = fopen("/sys/class/power_supply/battery/temp", "r");
	if(!battery_temp_file) {
		printf("battery_temp_file open error\n");
		return -1;
	}
	cpu_temp_file = fopen("/sys/class/thermal/thermal_zone6/temp", "r");
	if(!cpu_temp_file) {
		printf("cpu_temp_file open error\n");
		return -1;
	}
	battery_capacity_file = fopen("/sys/class/power_supply/battery/capacity", "r");
	if(!battery_capacity_file) {
		printf("battery_capacity_file open error\n");
		return -1;
	}
	battery_health_file = fopen("/sys/class/power_supply/battery/health", "r");
	if(!battery_health_file) {
		printf("battery_health_file open error\n");
		return -1;
	}
	battery_status_file = fopen("/sys/class/power_supply/battery/status", "r");
	if(!battery_status_file) {
		printf("battery_status_file open error\n");
		return -1;
	}

	for(;;) {
		fscanf(battery_temp_file, "%d", &battery_temp);
		if(battery_temp >= 40) {
			for(;;) {
				if(battery_temp < 40) break;
				if(

	fclose(battery_capacity_file);
	fclose(battery_temp_file);
	fclose(cpu_temp_file);
	fclose(battery_health_file);
	fclose(battery_status_file);
	for(i = 0;i < 4;i++) {
		fclose(cpu_freq_file[i]);
	}

	return 0;
}
