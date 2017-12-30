Проведем еще один эксперимент.

Реализуйте метод Generator.GenerateCallRunner() так, чтобы он порождал код следующего вида:
```
public class CallRunner : IRunner
{
    void PC1(C1 o) { }
    void PS1(S1 o) { }
    void PC2(C2 o) { }
    void PS2(S2 o) { }
    
    ...
    
    public void Call(bool isClass, int size, int count)
    {
      if (isClass && size == 1)
      {
          var o = new C1(); for (int i = 0; i < count; i++) PC1(o);
          return;
      }
      if (!isClass && size == 1)
      {
          var o = new S1(); for (int i = 0; i < count; i++) PS1(o);
          return;
      }
        
      ...
        
      throw new ArgumentException();
    }
}
```
