package ro.ubb.expression;

import ro.ubb.value.IValue;

public record ArithmeticExpresion(IExpression first, IExpression second, Operator op) implements IExpression {
    @Override
    public IValue evaluate() {
        return null;
    }
}
