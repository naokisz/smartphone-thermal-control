#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	int battery_temp;
	int cpu_temp;
	int battery_capacity;
	int cpu_freq;
	int i;
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

	system("su");
	battery_temp_file = fopen("/sys/class/thermal/thermal_zone6/temp", "r");
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
	system("chmod 666 /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq");
	system("chmod 666 /sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq");
	system("chmod 666 /sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq");
	system("chmod 666 /sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq");
	cpu_freq_file[0] = fopen("/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq", "r+");
	if(!cpu_freq_file) {
		printf("cpu_freq_file[0] open error\n");
		return -1;
	}
	cpu_freq_file[1] = fopen("/sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq", "r+");
	if(!cpu_freq_file) {
		printf("cpu_freq_file[1] open error\n");
		return -1;
	}
	cpu_freq_file[2] = fopen("/sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq", "r+");
	if(!cpu_freq_file) {
		printf("cpu_freq_file[2] open error\n");
		return -1;
	}
	cpu_freq_file[3] = fopen("/sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq", "r+");
	if(!cpu_freq_file) {
		printf("cpu_freq_file[3] open error\n");
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
		fscanf(battery_temp_file, "%d", battery_temp);

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
