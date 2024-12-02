#include "objects.hpp"

const Vertex Triangle::vertex[3] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{0.0f, 0.5f, 0.0f, 1.0f}} };  //2

const GLubyte Triangle::index[3] = { 0, 1, 2 };

const Vertex Square::vertex[4] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{0.5f, 0.5f, 0.0f, 1.0f}},   //2
    {{0.0f, 0.5f, 0.0f, 1.0f}} };  //3

const GLubyte Square::index[6] = { 0, 1, 2, 0, 2, 3 };

const Vertex Parallelogram::vertex[4] = {
    {{0.0f, 0.0f, 0.0f, 1.0f}},   //0
    {{0.5f, 0.0f, 0.0f, 1.0f}},   //1
    {{1.0f, 0.5f, 0.0f, 1.0f}},   //2
    {{0.5f, 0.5f, 0.0f, 1.0f}} };  //3

const GLubyte Parallelogram::index[6] = { 0, 1, 2, 0, 2, 3 };