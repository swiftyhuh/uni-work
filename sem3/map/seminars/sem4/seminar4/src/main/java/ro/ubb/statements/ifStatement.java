package ro.ubb.statements;

import ro.ubb.expression.IExpression;

public record ifStatement(
        IExpression condition,
        IStatement thenStatement,
        IStatement elseStatement) implements IStatement{

}
)
