
#pragma once
#include <hl.type.h>
#include <hl.macro.vargs.h>

//int hl_chars_format_u32();

int hlcf_u32(char *buffer, char *b_end, const char *format, const char *f_end, u32 value);
int hlcf_s32(char *buffer, char *b_end, const char *format, const char *f_end, s32 value);
int hlcf_u64(char *buffer, char *b_end, const char *format, const char *f_end, u64 value);
int hlcf_s64(char *buffer, char *b_end, const char *format, const char *f_end, s64 value);
int hlcf_f32(char *buffer, char *b_end, const char *format, const char *f_end, float value);
int hlcf_f64(char *buffer, char *b_end, const char *format, const char *f_end, double value);
int hlcf_str(char *buffer, char *b_end, const char *format, const char *f_end, const char *str);
int hlcf_ptr(char *buffer, char *b_end, const char *format, const char *f_end, void *pointer);


//int strf_vargs(char *buffer, char *b_end, const char *format, const char *types, void **args_list);

int hlcf_vlist(char *buffer, char *b_end, const char *format, va_list args_list);

