На этой практике мы проведем небольшое научное исследование. Мы выполним замеры времени для некоторых операций над классами и структурами, сравним их, объясним и поймем, в каких случаях использование структур дает выигрыш.

Сначала нужно создать типы данных, с которыми мы будем работать. Нам понадобятся классы и структуры с 512 полями! Очевидно, мы не хотим писать их вручную, и воспользуемся кодогенерацией.

[Скачайте проект](https://ulearn.me/Exercise/StudentZip?courseId=BasicProgramming&slideId=616826fa-d344-4292-9ab4-ec5c8ea83e1e)

Реализуйте метод Generator.GenerateDeclarations() так, чтобы он возвращал строку следующего вида:
```
struct S1
{
byte Value0;
}

class C1
{
byte Value0;
}

struct S2
{
byte Value0; byte Value1;
}

class C2
{
byte Value0; byte Value1;
}

struct S4
{
byte Value0; byte Value1; byte Value2; byte Value3;
}

class C4
{
byte Value0; byte Value1; byte Value2; byte Value3;
}
```

Классы имеют вид C1, C2, C4, C8 и т.д. Список индексов возьмите из Constants.FieldCounts.

Также реализуйте метод Generator.GenerateArrayRunner(), чтобы он возвращал строку следующего вида:
```
public class ArrayRunner : IRunner
  {
      void PC1()
      {
          var array = new C1[Constants.ArraySize];
          for (int i = 0; i < Constants.ArraySize; i++) array[i] = new C1();
        }
      void PS1()
      {
          var array = new S1[Constants.ArraySize];
      }
      
      ...
      
      public void Call(bool isClass, int size, int count)
      {
          if (isClass && size == 1)
          {
              for (int i = 0; i < count; i++) PC1();
              return;
          }
          if (!isClass && size == 1)
          {
              for (int i = 0; i < count; i++) PS1();
              return;
          }
          ...
        throw new ArgumentException();
      }
}
```
