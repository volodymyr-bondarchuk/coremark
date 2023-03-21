.. _coremark_sample:

CoreMark
########

.. contents::
   :local:
   :depth: 2

The sample demonstrates how to run the `CoreMark®`_ benchmark to evaluate performance of a core using `Zephyr Project`_.

.. _CoreMark®: https://www.eembc.org/coremark/

.. _Zephyr Project: http://docs.zephyrproject.org

Overview
********

The sample runs the CoreMark benchmark on the target CPU.
CoreMark evaluates the CPU efficiency by performing different algorithms, such as state machine, CRC calculation, matrix manipulation and list processing (find and sort).

Configuration
*************

CoreMark runs tests multiple times. The number of iterations is defined with the ``CONFIG_COREMARK_ITERATIONS`` option.
By default, the iteration quantity is set to the minimum time required for valid results.
For valid results, the test should be executed for at least 10 seconds.

CoreMark has three predefined run types, with the predefined data sizes, that are used for data algorithms:

* ``CONFIG_COREMARK_RUN_TYPE_PERFORMANCE`` - defines ``CONFIG_COREMARK_DATA_SIZE`` to 2000 bytes.
* ``CONFIG_COREMARK_RUN_TYPE_PROFILE`` - defines ``CONFIG_COREMARK_DATA_SIZE`` to 1200 bytes.
* ``CONFIG_COREMARK_RUN_TYPE_VALIDATION`` - defines ``CONFIG_COREMARK_DATA_SIZE`` to 500 bytes.

However, you can specify a custom ``CONFIG_COREMARK_DATA_SIZE`` value.
If you want to register your results, see the Submitting Results chapter in the `CoreMark GitHub`_ repository.

Additionally, the ``CONFIG_COREMARK_DATA_SIZE`` option requires available memory space.
By default, the ``CONFIG_COREMARK_MEMORY_METHOD_STACK`` option is selected.
In this case, the main thread stack is used for data allocation.
To change the main stack size, use the ``CONFIG_MAIN_STACK_SIZE`` option.

If you select the ``CONFIG_COREMARK_MEMORY_METHOD_MALLOC`` option, Zephyr :c:func:`k_malloc\k_free` functions will be used to allocate the memory in the heap.
Adjust the heap size with the ``CONFIG_HEAP_MEM_POOL_SIZE`` config option.

If you select the ``CONFIG_COREMARK_MEMORY_METHOD_STATIC`` option, data will be allocated to the RAM as a regular static variable.
In this case you do not need to be aware of the main thread stack size or heap memory pool size.

CoreMark can be executed in a multithread mode.
To specify a number of threads, use the ``CONFIG_COREMARK_THREADS_NUMBER`` option.
You can configure up to four threads.
In the multithread mode, CoreMark is executed in all threads simultaneously.
By default ``CONFIG_TIMESLICE_SIZE`` is set to 10 ms which imitates RTOS multithread usage.
However, in the final report thread execution is combined.
In multithread mode, the ``CONFIG_COREMARK_DATA_SIZE`` option is allocated for each thread separately.
Only the ``CONFIG_COREMARK_MEMORY_METHOD_STACK`` and ``CONFIG_COREMARK_MEMORY_METHOD_MALLOC`` memory methods can be used with multiple threads.
In case of the ``CONFIG_COREMARK_MEMORY_METHOD_STACK`` option, the data for all threads are allocated to the main thread stack.

Building and running
********************

An extra build flag ``CONFIG_COMPILER_OPT="-O3"`` is applied when running the benchmark build to achieve the best CoreMark results.
To build and flash sample run:

.. code-block:: console

   west build -b nrf52840dk_nrf52840
   west flash --skip-rebuild


After flashing, messages will appear in the corresponding console that describe the state of the benchmark.
To build for another board, change "nrf52840dk_nrf52840" above to that board's name.

Testing
=======

After programming the sample to your development kit, complete the following steps to test it:

1. Connect to the development kit with a terminal emulator (for example, PuTTY).
#. Reset your development kit.
#. The benchmark will launch on the application's start automatically.
#. Wait for all measurements to be complete.
   By default test will take approximately 11-13 seconds.
#. Wait for the console output.
   The results will be similar to the following example:

      .. code-block:: console

         *** Booting Zephyr OS build zephyr-v3.3.0-386-g8e18c5ce1d75 ***
         [00:00:00.511,291] <inf> app: Coremark sample for nrf52dk_nrf52832
         [00:00:30.858,703] <inf> app: (threads: 1, data size: 2000; iterations: 2000)

         2K performance run parameters for coremark.
         CoreMark Size    : 666
         Total ticks      : 395984
         Total time (secs): 12.084472
         Iterations/Sec   : 165.501645
         Iterations       : 2000
         Compiler version : GCC12.1.0
         Compiler flags   : -O3
         Memory location  : STACK
         seedcrc          : 0xe9f5
         [0]crclist       : 0xe714
         [0]crcmatrix     : 0x1fd7
         [0]crcstate      : 0x8e3a
         [0]crcfinal      : 0x4983
         Correct operation validated. See README.md for run and reporting rules.
         CoreMark 1.0 : 165.501645 / GCC12.1.0 -O3 / STACK
         [00:00:43.974,304] <inf> app: Coremark finished! RESET to restart ...

.. _CoreMark GitHub: https://github.com/eembc/coremark#submitting-results
