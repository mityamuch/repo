# Fund_Labs_4semestr
 | Lab | Mark |
| ------ | ------ |
| lab6.1 | finished |
| lab6.2 | finished|
| lab7.1 | Untested |
| lab7.2 | Untested |
| lab7.3 | Untested |
| lab7.4 | Untested |
| lab8.1 | Untested |
| lab8. | Untested |
| lab8. |Untested|

# lab6

## 0 

Опишите абстрактный класс **TeX_convertible**, содержащий единственную чистую виртуальную функцию с прототипом **std::string convert() const;**
, задачей которой является преобразование вызывающего объекта, тип которого наследует TeX_convertible, 
в строку с кодом на TeX, который при компиляции порождает математическую форму записи этого объекта.

## 1. 

Разработайте класс квадратной матрицы, наследующий класс **TeX_convertible.**
Класс должен содержать указатель на место в памяти, где располагаются элементы матрицы (вещественного типа данных) и её размерность (целое неотрицательное число). 
Для класса реализуйте необходимое число конструкторов (при этом хотя бы один из них должен принимать аргументы по умолчанию); 
перегрузите 
конструктор копирования;  
деструктор;  
оператор присваивания;  
арифметические операторы для сложения матриц, вычитания матриц, умножения матриц,  
умножения матрицы на число и числа на матрицу;  
операторы сравнения матриц на предмет полного равенства (epsilon принять равным 1e-6);  
индексатор для взятия значения из матрицы по индексам строки/столбца (отсчёт с 0);  
операторы вставки в поток и выгрузки из потока.  

Реализуйте дружественные методы вычисления определителя, нахождения обратной матрицы, нахождения транспонированной матрицы, 
вычисление следа матрицы и матричной экспоненты выполнения операции, должна быть сгенерирована исключительная ситуация 
(для каждого типа ошибки - свой тип исключительной ситуации), которая должна быть перехвачена и обработана в вызывающем коде.  

Продемонстрируйте работу с вашим классом: на вход программе подаётся файл, 
содержащий выражения с матрицами (каждое из выражений содержит одну из операций: сложение 
/ вычитание / умножение матриц, умножение матрицы на число, умножение числа на матрицу, сравнение матриц (==, !=); 
нахождение определителя матрицы; нахождение обратной матрицы; нахождение транспонированной матрицы; нахождение следа матрицы;
нахождение матричной экспоненты; формат представления данных в файле определите самостоятельно). 
Необходимо вычислить значения всех выражений и сгенерировать *TeX-файл* 
(выражения, при вычислении которых была сгенерирована исключительная ситуация, в выходной файл выписываться не должны), 
где каждое выражение будет иметь вид <исходное выражение> = <результат вычисления выражения>. 

>(optional) После генерации TeX-файла необходимо запустить его компиляцию и получить на выходе pdf-файл. 

>*Замечания*. Арифметические операции необходимо реализовать с помощью соответствующих операции присваивания:
например, операция + должна быть реализована с помощью операции +=. 
Необходимо продемонстрировать передачу аргументов в функции по значению и по ссылке; 
возврат объекта из функции.

## 2.


 Реализовать immutable-класс монома от нескольких переменных,
наследующий класс TeX_convertible. Класс должен содержать набор
уникальных однобуквенных имён переменных, соответствующие
именам переменных степени (целое неотрицательное число) и
коэффициент (целое число). В классе монома должны быть
определены и реализованы следующие сущности:

1.● Конструкторы (обязателен конструктор, принимающий на
вход строковое представление монома (типа char*); также
обязателен перегруженный конструктор копий);  
2.● Перегруженный деструктор;    
3.● Перегруженный оператор присваивания;  
4.● Перегруженные операторы для арифметических операций
между мономами: +, +=, -, -=, *, *=;  
5.● Перегруженные операторы для взятия частной производной
монома: /, /= (параметр типа char);  
6.● Перегруженные операторы для сравнения мономов на
предмет полного равенства: ==, !=;  
7.● Перегруженные операторы вставки в поток и выгрузки из
потока для корректного вывода/ввода монома.  

На основе реализованного класса монома необходимо
реализовать класс полинома от нескольких переменных (также
наследующий класс TeX_convertible).  
Класс полинома должен
представлять собой контейнер мономов на базе двусвязного списка;
в произвольный момент времени в полиноме не должны
присутствовать мономы, равные без учёта коэффициентов, а также
мономы с коэффициентом, равным нулю. В классе полинома
необходимо реализовать:  
1.● Конструкторы (обязателен конструктор, принимающий на
вход строковое представление полинома (типа char*); также
обязателен перегруженный конструктор копий);  
2.● Перегруженный деструктор;  
3.● Перегруженный оператор присваивания;  
4.● Перегруженные операторы для арифметических операций
между полиномами: +, +=, -, -=, *, *=;  
5.● Перегруженные операторы для взятия частной производной
полинома: /, /= (параметр типа char);  
6.● Перегруженные операторы для взятия смешанной (по
нескольким переменным) производной полинома: /, /=
(параметр типа char* - строка с именами переменных);  
7.● Перегруженные операторы для сравнения полиномов: ==,
!=;  
8● Перегруженные операторы вставки в поток и выгрузки из
потока для корректного ввода/вывода полинома; 
9.● Дружественный метод для проверки полинома на
однородность;  
10.● Дружественный метод для проверки полинома на
гармоничность.  

Для демонстрации работы класса полинома реализуйте
возможность обработки входного файла, содержащего выражения с
полиномами (каждое выражение содержит одну из операций:
сложение/вычитание/умножение полиномов; нахождение
смешанной производной по строке с именами переменных;
сравнение полиномов (==, !=); проверка полинома на однородность;
проверка полинома на гармоничность; формат представления
данных в файле определите самостоятельно). Необходимо
вычислить значения всех выражений и сгенерировать TeX-файл, где
каждое выражение будет иметь вид
<исходное выражение> = <результат вычисления выражения>.
>(optional) После генерации TeX-файла необходимо запустить его
компиляцию и получить на выходе pdf-файл.
Замечания. Арифметические операторы необходимо
реализовать с помощью соответствующих арифметических операций
с присваиванием (например, оператор + должен быть реализован с
помощью оператора +=). Продемонстрировать передачу аргументов
в функции по значению и по ссылке.

# lab7


## 0.
 Опишите абстрактный шаблонный класс binary_tree<T>,
представляющий собой абстракцию дерева поиска (тип элементов
указывается в единственном параметре шаблона). Класс должен
содержать три чистых виртуальных функции: добавления элемента в
дерево, удаления элемента из дерева, поиска элемента в дереве по
значению. Конструктор класса должен принимать в качестве
параметра шаблонный компаратор (правило вычисления отношения
порядка между данными в узлах дерева), реализованный в виде
объекта стратегии (см. паттерн “Стратегия”).
## 1.
 На основе класса из задания 1 реализуйте шаблонные классы
красно-чёрного дерева и АВЛ-дерева. Сгенерируйте
псевдослучайные выборки данных и на их основе проведите
сравнительный анализ времени работы и количества операций
поворотов в алгоритмах вставки / удаления / поиска для
красно-чёрного дерева и АВЛ-дерева.
## 2.
 На основе классов из заданий 1 и 2 реализуйте шаблонный класс
relation<T>, содержащий в себе односвязный список данных типа T,
а также список индексов типа binary_tree<T> (каждое дерево должно
быть построено поверх данных, хранящихся в односвязном списке;
компараторы могут быть различны). Предоставьте функционал
добавления и удаления данных (с сохранением корректности
индексов), поиска данных по значению, а также добавления и
удаления индексов (в виде реализованных классов из задания 2).
## 3.
 Продемонстрируйте работу класса из задания 3 на примере
размещения в объекте данных из файла, каждая строка которого
имеет следующий формат:
<datetime> <username>: <message>
Перед добавлением данных объект должен содержать единственный
индекс по полю datetime структуры. После добавления данных
необходимо добавить в объект индексы, описанные ниже, и
продемонстрировать поиск данных посредством добавленных
индексов:
- по полю username (лексографическое сравнение строк с
учётом регистра);
- по полю message (лексографическое сравнение строк без учёта
регистра);
- первично по полю datetime, вторично по полю username
(лексографическое сравнение строк без учёта регистра).
## 4.
 Продемонстрируйте работу класса из задания 3 на примере
размещения в объекте данных из файла, имеющих следующий
формат:
<Фамилия> <Имя> <Отчество>
{
<Договор #id> нач. <дата начала> кон. <дата окончания> <Стоимость>
<Договор #id> нач. <дата начала> кон. нв <Стоимость>
...
}
Перед добавлением данных объект не должен содержать индексов.
После добавления данных необходимо добавить и
продемонстрировать работу следующих индексов (целевыми
данными для индексирования является информация о договорах):
- первично по ФИО владельца, вторично по id договора;
- по длительности договора;
- по стоимости договора.


# lab8

## 1. 
Реализуйте класс memory, содержащий динамический массив
размером N байт (N передаётся как параметр конструктора). Класс
должен предоставлять возможность резервирования блока памяти
размера n и освобождения выделенного блока памяти (методы
allocate/deallocate соответственно; доступ к памяти извне не
разрешается). При невозможности выделения памяти необходимо
прибегнуть к уплотнению кучи, а при невозможности выделения
памяти после уплотнения должна быть сгенерирована и перехвачена
исключительная ситуация. Для выделения памяти реализуйте
алгоритм первого подходящего. Для освобождения памяти
рассмотрите два подхода: алгоритм освобождения в
рассортированном списке и алгоритм освобождения с
дескрипторами границ. Методы allocate и deallocate должны
описывать последовательность действий, в которой общие для обоих
алгоритмов выделения / освобождения памяти шаги реализованы, а
различающиеся реализованы в подклассах класса memory (см.
паттерн “Шаблонный метод”). Продемонстрируйте работу
реализованных классов на примере обработки файла следующего
вида:

100

var1=allocate(10);

var2=var1;

var3=allocate(20);

var1=var3;

dealloc(var1);

dealloc(var2);

Первая строка файла содержит число N - размер динамической кучи.

Дальнейшие строки файла могут содержать инструкции
инициализации переменных и присваивания им значения, а также
освобождения выделенной памяти. 

Операция “=” является поверхностным копированием (не приводит к выделению нового
блока памяти). 
При попытке обращения к недоступной памяти или
её очистки должна быть сгенерирована и обработана
исключительная ситуация. После обработки файла выведите на
консоль количество “утекших” блоков памяти и их адреса 

(отсчёт с 0) и размеры в порядке нахождения в памяти. 

Проведите сравнительный анализ эффективности реализованных алгоритмов.

## 2. 
Реализуйте класс memory, содержащий динамический массив
размером N байт (N передаётся как параметр конструктора). Класс
должен предоставлять возможность резервирования блока памяти
размера n при помощи метода allocate (доступ извне напрямую к
выделенной памяти не разрешается). При невозможности выделения
памяти необходимо прибегнуть к уплотнению кучи, а при
невозможности выделения памяти после уплотнения должна быть
сгенерирована и перехвачена исключительная ситуация. Выделение
и освобождение выделенной памяти реализуйте с использованием
алгоритмов системы двойников. Продемонстрируйте работу класса
на примере обработки файла следующего вида:

100

{

PrintVars;

var1=new(10);

{

var2=new(25);

PrintVars;

{

{

var3=new(7);

}

var5=new(11);

PrintVars;

var21=new(23);

}

var22=new(85);

}

var2=new(9);

PrintVars;

}

Первая строка файла содержит число N - размер динамической кучи.
Фигурные скобки определяют блоки кода, ограничивающие области
видимости переменных. Инструкция new запрашивает из объекта
класса memory блок памяти заданного размера для переменной,
стоящей слева от оператора инициализации (“=”). Инструкция
PrintVars выводит доступные из текущего блока кода доступные
переменные с указанием выделенного под них размера в памяти.
При покидании блока, память под объявленные в блоке переменные
не освобождается автоматически. При невозможности выделения
памяти, выделение должно быть повторно произведено после сборки
мусора; в случае повторного неудачного выделения памяти должна
быть сгенерирована и обработана исключительная ситуация.

## 3.
 Напишите программу для анализа последовательности вызовов
функций (подпрограмм) для некоторого языка программирования
(вы можете использовать синтаксис одного из языков: C, C++,
python, C#, Java, JavaScript). На вход программе (через аргументы
командной строки) подаётся набор путей к текстовым файлам,
содержащих исходный код программы. Считается, что исполнение
кода начинается с первого файла в списке, порядок остальных
файлов не важен. Ваша программа должна определить все
вызываемые функции (методы, подпрограммы), построить дерево
вызовов для каждой функции, найти рекурсивные (прямо или
косвенно) функции (без учёта значений параметров функций), для
каждой такой функции f построить все возможные стеки вызовов
функций, приводящей к первому рекурсивному (прямому или
косвенному) вызову f. Также необходимо определить все
нереализованные функции. В передаваемых файлах могут
присутствовать директивы подключения других файлов (#include,
import, using, …), поиск функции необходимо осуществлять только в
передаваемых файлах. Обработайте некоторые типичные ошибки:
отсутствие импортируемого файла, неверное количество аргументов
у функции. Примечание: считается, что грубых синтаксических
ошибок в файлах нет (скобки расставлены корректно, типы
передаваемых и возвращаемых аргументов корректны, нет
потерянных параметров); все функции имеют фиксированное
количество параметров, параметров по умолчанию нет.
