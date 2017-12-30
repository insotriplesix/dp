using System;
using System.Text;

namespace Profiling
{
    class Generator
    {
        public static string GenerateDeclarations()
        {
            var declarations = new StringBuilder();

            foreach (var index in Constants.FieldCounts)
            {
                declarations.Append(CreateDeclaration("struct S", index));
                declarations.Append(CreateDeclaration("class C", index));
            }

            return declarations.ToString();
        }

        public static string CreateDeclaration(string prefix, int index)
        {
            var declaration = new StringBuilder(prefix + index + "\n{\n");

            for (var j = 0; j < index; ++j)
            {
                declaration.AppendFormat("byte Value{0}; ", j);
            }

            declaration.Append("\n}\n");

            return declaration.ToString();
        }

        public static string GenerateArrayRunner()
        {
            var result =
				new StringBuilder("public class ArrayRunner : IRunner \n{\n");

            foreach (var index in Constants.FieldCounts)
            {
                result.AppendFormat("void PC{0}()\n{{\n" +
                    "var array = new C{0}[Constants.ArraySize];\n" +
                    "for (int i = 0; i < Constants.ArraySize; i++) "+
                    "array[i] = new C{0}();\n}}void PS{0}()\n{{\n" +
                    "var array = new S{0}[Constants.ArraySize];\n}}", index);
            }

            result.Append("public void Call(bool isClass, int size, int count)\n{\n");

            foreach (var index in Constants.FieldCounts)
            {
				result.AppendFormat("if (isClass && size == {0})\n{{\n" +
                    "for (int i = 0; i < count; i++) " +
					"PC{0}();\nreturn;\n}}\nif (!isClass && size == {0})\n{{\n" +
                    "for (int i = 0; i < count; i++) PS{0}();\nreturn;\n}}\n", index);
            }

            result.Append("throw new ArgumentException();\n}\n}");

            return result.ToString();
        }

        public static string GenerateCallRunner()
        {
            throw new NotImplementedException();
        }
    }
}
