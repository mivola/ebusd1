/*
 * Copyright (C) John Baier 2014-2015 <ebusd@ebusd.eu>
 *
 * This file is part of ebusd.
 *
 * ebusd is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ebusd is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ebusd. If not, see http://www.gnu.org/licenses/.
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "result.h"
#include "data.h"
#include "message.h"
#include <stdint.h>

/** \file main.h */

/** A structure holding all program options. */
struct options
{
	const char* device; //!< eBUS device (serial device or ip:port) [/dev/ttyUSB0]
	bool noDeviceCheck; //!< skip serial eBUS device test
	bool readonly; //!< read-only access to the device

	const char* configPath; //!< path to CSV configuration files [/etc/ebusd]
	int checkConfig; //!< check CSV config files (!=0) and optionally dump (2), then stop
	int pollInterval; //!< poll interval in seconds, 0 to disable [5]

	unsigned char address; //!< own bus address [FF]
	bool answer; //!< answer to requests from other masters
	int acquireTimeout; //!< bus acquisition timeout in us [9400]
	int acquireRetries; //!< number of retries for bus acquisition [2]
	int sendRetries; //!< number of retries for failed sends [2]
	int receiveTimeout; //!< timeout for receiving answer from slave in us [15000]
	int masterCount; //!< expected number of masters for arbitration [5]
	bool generateSyn; //!< enable AUTO-SYN symbol generation

	bool foreground; //!< run in foreground
	uint16_t port; //!< port to listen for command line connections [8888]
	bool localOnly; //!< listen on 127.0.0.1 interface only
	uint16_t httpPort; //!< optional port to listen for HTTP connections, 0 to disable [0]
	string htmlPath; //!< path for HTML files served by the HTTP port [/var/ebusd/html]

	const char* logFile; //!< log file name [/var/log/ebusd.log]
	bool logRaw; //!< log each received/sent byte on the bus

	bool dump; //!< dump received bytes
	const char* dumpFile; //!< dump file name [/tmp/ebus_dump.bin]
	int dumpSize; //!< maximum size of dump file in kB [100]
};

/**
 * Load the message definitions from the configuration files.
 * @param templates the @a DataFieldTemplates to load the templates into.
 * @param messages the @a MessageMap to load the messages into.
 * @param verbose whether to verbosely log problems.
 * @return the result code.
 */
result_t loadConfigFiles(DataFieldTemplates* templates, MessageMap* messages, bool verbose=false);

#endif // MAIN_H_
