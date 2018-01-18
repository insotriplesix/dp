Помните класс Vector из позапрошлой практики? Скорее всего, он был написан ужасно, с открытыми полями и всем прочим.

Как правило, такие структуры данных делают read-only.

В пространстве имен ReadOnlyVectorTask сделайте класс ReadOnlyVector с двумя публичными readonly-полями X и Y, которые устанавливаются в конструкторе.

ReadOnlyVector должен содержать метод Add(ReadOnlyVector other), который возвращает сумму векторов.

При работе с readonly классами часто хочется изготовить вектор "такой же, но с другим значением поля X или Y". Обеспечьте такую функциональность с помощью методов WithX(double) и WithY(double)