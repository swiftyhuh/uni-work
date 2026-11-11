package ro.ubb.statements;

import ro.ubb.expression.IExpression;
import ro.ubb.state.ProgramState;

public record AssignmentStatement(String variableName, IExpression expression) implements iStatement {
    @Override
    public void execute(ProgramState programState) {
    }
}
