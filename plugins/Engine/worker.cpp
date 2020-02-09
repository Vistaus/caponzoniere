/*
 * Copyright (C) 2020  Lorenzo Torracchi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * caponzoniere is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "worker.h"

#include <QDebug>

#include <chrono>
#include <thread>

Worker::Worker() {
	this->running = true;
}

Worker::~Worker() {
}

void Worker::process() {
	for (int i = 10;i >0 && this->running;i--) {
		emit songChanged(QString::number(i));
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
    while (this->running) {
        emit songChanged(this->getNextTitle());
        std::this_thread::sleep_for(std::chrono::seconds(7));
        qDebug() << "song change emitted";
    }
}

void Worker::stop() {
    qDebug() << "STOPPED";
    this->running = running;
}

QString Worker::getNextTitle() {
    return this->titles.at(rand() % this->titles.size());
}

void Worker::setTitles(QStringList titles) {
    this->titles = titles;
}