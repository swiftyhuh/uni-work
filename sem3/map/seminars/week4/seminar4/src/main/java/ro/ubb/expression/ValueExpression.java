package ro.ubb.expression;

import ro.ubb.value.IValue;

public record ValueExpression(IValue value) implements IExpression {
    @Override
    public IValue evaluate(){
        return value;
    }
}
