package ro.ubb.expression;

import ro.ubb.value.IValue;

public record VariableExpression(String variableName) implements IExpression {
    @Override
    public IValue evaluate(){
        return null;
    }
}
