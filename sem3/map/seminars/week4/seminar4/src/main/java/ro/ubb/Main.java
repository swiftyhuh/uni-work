package ro.ubb;

import ro.ubb.expression.*;
import ro.ubb.statements.*;
import ro.ubb.type.BoolType;
import ro.ubb.type.IntType;
import ro.ubb.value.BoolValue;
import ro.ubb.value.IntValue;

import java.lang.reflect.Array;
import java.util.List;

//TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or
// click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
public class Main {
    static void main() {
        //int a;
        //int b;
        //bool c;
        //a=5;
        //b=a*2-3;
        //c=true or false;
        //if c then print(b) else print(a)

        iStatement[] statements = new iStatement[]{
                new VariableDeclarationStatement(IntType.INSTANCE, "a"),
                new VariableDeclarationStatement(IntType.INSTANCE, "b"),
                new VariableDeclarationStatement(BoolType.INSTANCE, "c"),

                new AssignmentStatement("a", new ValueExpression(new IntValue(5))),

                new AssignmentStatement("b",
                        new ArithmeticExpresion(
                                new ArithmeticExpresion(
                                        new VariableExpression("a"),
                                        new ValueExpression(new IntValue(5)),
                                        Operator.MUL),
                                new ValueExpression(new IntValue(3)),
                                Operator.SUB)),

                new AssignmentStatement("c",
                        new BooleanExpression(
                                new ValueExpression(new BoolValue(true)),
                                new ValueExpression(new BoolValue(false)),
                                BooleanOperator.OR)),

                new IfStatement(
                        new VariableExpression("c"),
                        new PrintStatement(new VariableExpression("b")),
                        new PrintStatement(new VariableExpression("a")))
        };

        iStatement program = statements[statements.length-1];
        for(int i= statements.length-2; i>=0; i--){
            program = new CompoundStatement(statements[i],program);
        }
        IO.println(program);

    }
}
