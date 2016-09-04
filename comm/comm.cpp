#include "comm.h"

void print_log(const char *msg,const char *func,int line)
{
	time_t timenow;
	time(&timenow);//获取当前时间
	struct tm *timep;
	timep=localtime(&timenow);
	char *time=asctime(timep);
	int size=strlen(time);
	time[size-1]='\0';
	
	std::cout<<size<<time<<" in function "<<func<<" "<<line<<":"<<msg<<std::endl;//转换成本地时间,转换时间格式为标准UNIX时间格式
//std::cout<<asctime(gmtime(&timep))<<" in function "<<func<<" "<<line<<":"<<msg<<std::endl;//转换成格林威治时间。
}

//  struct tm {
//     int tm_sec;         /* seconds */
//     int tm_min;         /* minutes */
//     int tm_hour;        /* hours */
//     int tm_mday;        /* day of the month */
//     int tm_mon;         /* month */
//     int tm_year;        /* year */
//     int tm_wday;        /* day of the week */
//     int tm_yday;        /* day in the year */
//     int tm_isdst;       /* daylight saving time */
//  };
//time_t time(time_t *t);
//char *asctime(const struct tm *tm);
//char *asctime_r(const struct tm *tm, char *buf);
//char *ctime(const time_t *timep);
//char *ctime_r(const time_t *timep, char *buf);
//struct tm *gmtime(const time_t *timep);
//struct tm *gmtime_r(const time_t *timep, struct tm *result);
//struct tm *localtime(const time_t *timep);
//struct tm *localtime_r(const time_t *timep, struct tm *result);
//time_t mktime(struct tm *tm);

