#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "backup.hpp"

TEST_CASE("Tabela de Decisao - Ausencia de Backup.parm", "[tabela_decisao]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = false;
    estado.data_hd = 1000;
    estado.data_pendrive = 0;

    REQUIRE(DeterminarAcaoFicheiro(false, Operacao::BACKUP, estado) == Acao::IMPOSSIVEL);
}

TEST_CASE("Coluna 1: Backup - Ficheiro no HD e ausente no Pen-drive", "[coluna1]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = false;
    estado.data_hd = 1000;
    estado.data_pendrive = 0;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::BACKUP, estado) ==
            Acao::COPIAR_HD_PARA_PENDRIVE);
}

TEST_CASE("Coluna 2: Backup - Ficheiro no HD mais recente que no Pen-drive", "[coluna2]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = true;
    estado.data_hd = 2000;
    estado.data_pendrive = 1000;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::BACKUP, estado) ==
            Acao::COPIAR_HD_PARA_PENDRIVE);
}

TEST_CASE("Coluna 3: Backup - Ficheiros com a mesma data no HD e Pen-drive", "[coluna3]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = true;
    estado.data_hd = 1500;
    estado.data_pendrive = 1500;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::BACKUP, estado) ==
            Acao::FAZ_NADA);
}

TEST_CASE("Coluna 4: Backup - Ficheiro no Pen-drive mais recente que no HD", "[coluna4]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = true;
    estado.data_hd = 1000;
    estado.data_pendrive = 2000;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::BACKUP, estado) ==
            Acao::ERRO);
}

TEST_CASE("Coluna 5: Restaura - Ficheiro no HD mas ausente no Pen-drive", "[coluna5]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = false;
    estado.data_hd = 1000;
    estado.data_pendrive = 0;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::RESTAURACAO, estado) ==
            Acao::ERRO);
}

TEST_CASE("Coluna 6: Restaura - Ficheiro no Pen-drive mais antigo que no HD", "[coluna6]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = true;
    estado.data_hd = 2000;
    estado.data_pendrive = 1000;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::RESTAURACAO, estado) ==
            Acao::ERRO);
}

TEST_CASE("Coluna 7: Restaura - Ficheiros com a mesma data no HD e Pen-drive", "[coluna7]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = true;
    estado.data_hd = 1800;
    estado.data_pendrive = 1800;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::RESTAURACAO, estado) ==
            Acao::FAZ_NADA);
}

TEST_CASE("Coluna 8: Restaura - Ficheiro no Pen-drive mais recente que no HD", "[coluna8]") {
    EstadoFicheiro estado;
    estado.existe_hd = true;
    estado.existe_pendrive = true;
    estado.data_hd = 1000;
    estado.data_pendrive = 2000;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::RESTAURACAO, estado) ==
            Acao::COPIAR_PENDRIVE_PARA_HD);
}

TEST_CASE("Coluna 9: Backup - Ficheiro inexistente no HD e no Pen-drive", "[coluna9]") {
    EstadoFicheiro estado;
    estado.existe_hd = false;
    estado.existe_pendrive = false;
    estado.data_hd = 0;
    estado.data_pendrive = 0;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::BACKUP, estado) ==
            Acao::ERRO);
}

TEST_CASE("Coluna 10: Backup - Ficheiro ausente no HD mas presente no Pen-drive", "[coluna10]") {
    EstadoFicheiro estado;
    estado.existe_hd = false;
    estado.existe_pendrive = true;
    estado.data_hd = 0;
    estado.data_pendrive = 1200;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::BACKUP, estado) ==
            Acao::FAZ_NADA);
}

TEST_CASE("Coluna 11: Restaura - Ficheiro inexistente no HD e no Pen-drive", "[coluna11]") {
    EstadoFicheiro estado;
    estado.existe_hd = false;
    estado.existe_pendrive = false;
    estado.data_hd = 0;
    estado.data_pendrive = 0;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::RESTAURACAO, estado) ==
            Acao::ERRO);
}

TEST_CASE("Coluna 12: Restaura - Ficheiro ausente no HD e presente no Pen-drive", "[coluna12]") {
    EstadoFicheiro estado;
    estado.existe_hd = false;
    estado.existe_pendrive = true;
    estado.data_hd = 0;
    estado.data_pendrive = 1400;

    REQUIRE(DeterminarAcaoFicheiro(true, Operacao::RESTAURACAO, estado) ==
            Acao::COPIAR_PENDRIVE_PARA_HD);
}