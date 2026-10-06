===============================================================================

# Sistema de Backup com TDD e Tabela de Decisão

===============================================================================

1. Requisitos de Ambiente:
   - Linux / WSL (Ubuntu)
   - Compilador: g++ (suporte a C++11 ou superior)
   - Utilitários: make, git, gcov, cppcheck, cpplint, valgrind, doxygen

2. Instruções de Compilação e Execução:
   - Compilar o projeto e executar a suíte de testes:
     $ make test

   - Limpar arquivos compilados, temporários e relatórios:
     $ make clean

3. Verificação de Cobertura de Código (gcov):
   - Executa os testes e gera a análise de cobertura anotada em 'backup.cpp.gcov':
     $ make gcov

4. Análise Estática e Estilo de Código:
   - Executa as checagens com cppcheck e cpplint:
     $ make check

5. Verificação Dinâmica de Memória (Valgrind):
   - Executa os testes sob monitoramento de vazamentos de memória:
     $ make valgrind

6. Geração da Documentação (Doxygen):
   - Gera a documentação em formato HTML no diretório 'html/':
     $ make doc

7. Histórico do Desenvolvimento (TDD):
   - O diretório versionado '.git' está incluído na raiz deste arquivo compactado,
     contendo todo o histórico de ciclos TDD (Red-Green-Refactor) com mais de 30 commits.
===============================================================================
