#1. 
##Генерация псевдослучайных чисел в random: 
Алгоритм, создающий последовательность почти независимых друг от 
дргуа чисел, которые подчиняяются некоторому распределению.
##Seed:
Большое, обычно, число, которое используется для начала генерации 
последовательности псевдо-случайных чисел
##Generator:
Генератор , который по встроенному алгоритму и
seed'у строит последовательность псевдо-случайных чисел
##Distribution:
Функция, которой подчиняется вероятность выпадения чисел в 
последовательности псевдо-случайных чиселл

#2.
##Iterator
Структура данных, которая «указывает» на некоторый элемент контейнера, 
и (для некоторых контейнеров) умеет переходить к 
предыдущему/следующему элементу.
##Range
Обычно, пара итераторов, которые указывают на начало и конец 
рассматриваемого диапазона элементов какого-то контейнера. Отличие от 
контейнера заключается в том, что элементы не хранятся в диапазоне, он 
[диапазон] только указывает на границы нахождения элементов в памяти.
##Usage of iterators
Функционал итераторов разрабатывался для удобной работы с памятью. 
Итераторы универсальны и используются для работы с различными 
контейнерами, что уменьшает количество одинакового по смыслу кода 
и позволяет делать универсальные функции. 
