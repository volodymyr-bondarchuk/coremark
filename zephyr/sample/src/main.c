/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "coremark_zephyr.h"

LOG_MODULE_REGISTER(app, LOG_LEVEL_INF);

int main(void)
{
	LOG_INF("Coremark sample for %s", CONFIG_BOARD);
	LOG_INF("(threads: %d, data size: %d; iterations: %d)\n",
		CONFIG_COREMARK_THREADS_NUMBER,
		CONFIG_COREMARK_DATA_SIZE,
		CONFIG_COREMARK_ITERATIONS);

	coremark_run();

	LOG_INF("Coremark finished! RESET to restart ...\n");

	return 0;
}
