#ifndef BACKUP_HPP_
#define BACKUP_HPP_

#include <ctime>
#include <string>

/**
 * Tipo de operação solicitada pelo utilizador.
 */
enum class Operacao {
    BACKUP,
    RESTAURACAO
};

/**
 * Ações resultantes da tabela de decisão.
 */
enum class Acao {
    COPIAR_HD_PARA_PENDRIVE,
    COPIAR_PENDRIVE_PARA_HD,
    FAZ_NADA,
    ERRO,
    IMPOSSIVEL
};

/**
 * Estado e metadados de um ficheiro sob análise.
 */
struct EstadoFicheiro {
    bool existe_hd;
    bool existe_pendrive;
    std::time_t data_hd;
    std::time_t data_pendrive;
};

/*****
* Função: DeterminarAcaoFicheiro
* Descrição:
*   Avalia o estado de um ficheiro em relação ao HD e Pen-drive
*   e determina a ação adequada com base na tabela de decisão de espelhamento.
* Parâmetros:
*   tem_backup_parm - Booleano indicando a presença do ficheiro de controlo.
*   operacao        - Operacao::BACKUP ou Operacao::RESTAURACAO.
*   estado          - Estrutura contendo existência e datas do ficheiro nos destinos.
* Valor retornado:
*   Acao a ser tomada (COPIAR_HD_PARA_PENDRIVE, COPIAR_PENDRIVE_PARA_HD, FAZ_NADA, ERRO ou IMPOSSIVEL).
* Assertiva de entrada:
*   (!estado.existe_hd || estado.data_hd >= 0) &&
*   (!estado.existe_pendrive || estado.data_pendrive >= 0)
* Assertiva de saída:
*   retorno == Acao::IMPOSSIVEL || retorno == Acao::COPIAR_HD_PARA_PENDRIVE ||
*   retorno == Acao::COPIAR_PENDRIVE_PARA_HD || retorno == Acao::FAZ_NADA ||
*   retorno == Acao::ERRO
*****/
Acao DeterminarAcaoFicheiro(bool tem_backup_parm,
                           Operacao operacao,
                           const EstadoFicheiro& estado);

#endif  // BACKUP_HPP_