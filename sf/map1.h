#pragma once
#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 19;//размер карты высота
const int WIDTH_MAP = 26;//размер карты ширина 


sf::String TileMap[HEIGHT_MAP] = {
	"q00000000000s00000000000]", 
	"1mmmmmmmmmmm1mmmmmmmmmmm1",
	"1mq0]mq000]m1mq000]mq0]m1",
	"1mz0.mz000.m5mz000.mz0.m1",
	"1mmmmmmmmmmmmmmmmmmmmmmm1",
	"1m<0>m6m<000s000>m6m<0>m1",
	"1mmmmm1mmmmm1mmmmm1mmmmm1",
	"z000]md000>m5m<000amq000.",
	"----1m1mmmmmmmmmmm1m1----",
	"0000.m5mq00>-<00]m5mz0000",
	"t----mmm1--*-*--1mmm----p",
	"0000]m6mz0000000.m6mq0000",
	"----1m1mmmmmmmmmmm1m1----",
	"q000.m1m<000s000>m1mz000]",
	"1mmmmm5mmmmm1mmmmm5mmmmm1",
	"1mq0]mmmq0]m1mq0]mmmq0]m1",
	"1mz0w000w0.m5mz0w000w0.m1",
	"1mmmmmmmmmmmmmmmmmmmmmmm1",
	"z00000000000000000000000.",
};
