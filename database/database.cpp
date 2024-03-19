//
// Created by spiderman on 24-3-10.
//
#include "database.h"
#include <iostream>

mos::mos(const mos& mos_i) : m_sort(mos_i.m_sort), m_name(mos_i.m_name), m_source(mos_i.m_source), m_gate(mos_i.m_gate), m_drain(mos_i.m_drain), w_width(mos_i.w_width), w_length(mos_i.w_length), m_x(mos_i.m_x), m_f(mos_i.m_f) {}

