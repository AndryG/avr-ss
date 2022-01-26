#pragma once
#include <stdint.h>
#include <stdbool.h>

// Тип переменной для указания задержки выполнения. Можно увеличить директивой QT_DELAY_SIZE_16 (по ум. 8 бит)
#ifdef QT_DELAY_SIZE_16
  typedef uint16_t qtDelay;
#else
  typedef uint8_t qtDelay;
#endif

#ifndef QT_TASK_COUNT
#define QT_TASK_COUNT         10
#endif

// Код выхода
#ifndef QT_QUEUE_OVERFLOW_CODE
#define QT_QUEUE_OVERFLOW_CODE EXIT_FAILURE
#endif

// Тип указателя на функцию задачи
typedef void(*qtTaskPtr)(void);

// Инициализация очереди
void qtInit(void);

// Добавить задачу в очередь
void qtTask(qtTaskPtr ptr, qtDelay tick);

// Вызывается при каждом "tick", проводит отсчет задержки
void qtDecrementDelay(void);

// Пытается выполненить одну задачу из очереди
void qtDispatch(void);

// Пытается выполненить одну задачу из очереди. Вернет true, если задача вызывалась
bool qtDispatch2(void);
