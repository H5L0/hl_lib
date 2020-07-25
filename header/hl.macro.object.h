#pragma once



#define HLFCA(obj, function , ...) obj->fc->function(obj, __VA_ARGS__)

#define HLFC(obj, function) obj->fc->function(obj)

//#define HLFC(obj, function , args) obj->fc->function(obj, args


//wn1 = HLFCA(tw->stream, Write, chars, wn1);
//HLFC(tw->stream, Flush);



