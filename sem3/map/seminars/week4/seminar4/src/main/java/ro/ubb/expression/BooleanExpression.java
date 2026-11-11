package ro.ubb.expression;

import ro.ubb.value.IValue;

public record BooleanExpression(IExpression first, IExpression second, BooleanOperator op) implements IExpression{
    @Override
    public IValue evaluate() {
        return null;
    }
}
