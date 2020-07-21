#pragma once
#include <hl.type.h>


//#hl_string_format_u32()
//#hl_string_format_vargs()

//#hl_strf_u32

int strf_u32(char *buffer, char *b_end, const char *format, const char *f_end, u32 value);
int strf_s32(char *buffer, char *b_end, const char *format, const char *f_end, s32 value);

int strf_u64(char *buffer, char *b_end, const char *format, const char *f_end, u64 value);
int strf_s64(char *buffer, char *b_end, const char *format, const char *f_end, s64 value);

int strf_f32(char *buffer, char *b_end, const char *format, const char *f_end, float value);
int strf_f64(char *buffer, char *b_end, const char *format, const char *f_end, double value);

int strf_str(char *buffer, char *b_end, const char *format, const char *f_end, const char *str);


int strf_vargs(char *buffer, char *b_end, const char *format, const char *types, void **args_list);


#include <hl.macro.vargs.h>
int strf_vlist(char *buffer, char *b_end, const char *format, va_list args_list);

int hl_chars_format_u32();
int hl_cf_u32();


