// PolyLine class
//
// PolyLine is a ShapeComposite made of Points with generic Container.
// Hence, it is as a specialization of ShapeComposite.
//
// Tobias Bilgeri, 14.02.2024
#pragma once
#include "Point.h"
#include "ShapeComposite.h"

template<template<typename> class Container> 
class PolyLine : public ShapeComposite<Point, Container> {};