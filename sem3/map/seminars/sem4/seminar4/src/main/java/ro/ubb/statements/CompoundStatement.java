package ro.ubb.statements;

public record CompoundStatement(
        IStatement firstStatement,
        IStatement secondStatement) implements  IStatement{

    @Override


}

