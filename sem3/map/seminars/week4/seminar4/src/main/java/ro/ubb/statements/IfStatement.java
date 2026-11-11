package ro.ubb.statements;

import ro.ubb.expression.IExpression;
import ro.ubb.state.ProgramState;

import java.util.Objects;

public record IfStatement(IExpression condition, iStatement thenStatement,
                          iStatement elseStatement) implements iStatement {
    @Override
    public void execute(ProgramState programState) {
    }

    @Override
    public boolean equals(Object o) {
        if (!(o instanceof IfStatement that)) return false;
        return Objects.equals(condition, that.condition) &&
                Objects.equals(thenStatement, that.thenStatement) &&
                Objects.equals(elseStatement, that.elseStatement);
    }

    @Override
    public int hashCode() {
        return Objects.hash(condition, thenStatement, elseStatement);
    }
}
