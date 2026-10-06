#include "backup.hpp"
#include <cassert>

Acao DeterminarAcaoFicheiro(bool tem_backup_parm,
                           Operacao operacao,
                           const EstadoFicheiro& estado) {
    // Assertivas de entrada
    assert(!estado.existe_hd || estado.data_hd >= 0);
    assert(!estado.existe_pendrive || estado.data_pendrive >= 0);

    if (!tem_backup_parm) {
        return Acao::IMPOSSIVEL;
    }

    if (operacao == Operacao::BACKUP) {
        if (estado.existe_hd && !estado.existe_pendrive) {
            return Acao::COPIAR_HD_PARA_PENDRIVE;
        }
        if (estado.existe_hd && estado.existe_pendrive) {
            if (estado.data_pendrive < estado.data_hd) {
                return Acao::COPIAR_HD_PARA_PENDRIVE;
            }
            if (estado.data_pendrive == estado.data_hd) {
                return Acao::FAZ_NADA;
            }
            if (estado.data_pendrive > estado.data_hd) {
                return Acao::ERRO;
            }
        }
        if (!estado.existe_hd && !estado.existe_pendrive) {
            return Acao::ERRO;
        }
        if (!estado.existe_hd && estado.existe_pendrive) {
            return Acao::FAZ_NADA;
        }
    } else if (operacao == Operacao::RESTAURACAO) {
        if (estado.existe_hd && !estado.existe_pendrive) {
            return Acao::ERRO;
        }
        if (estado.existe_hd && estado.existe_pendrive) {
            if (estado.data_pendrive < estado.data_hd) {
                return Acao::ERRO;
            }
            if (estado.data_pendrive == estado.data_hd) {
                return Acao::FAZ_NADA;
            }
            if (estado.data_pendrive > estado.data_hd) {
                return Acao::COPIAR_PENDRIVE_PARA_HD;
            }
        }
        if (!estado.existe_hd && !estado.existe_pendrive) {
            return Acao::ERRO;
        }
        if (!estado.existe_hd && estado.existe_pendrive) {
            return Acao::COPIAR_PENDRIVE_PARA_HD;
        }
    }
//  Caso não seja possível determinar a ação, retorna ERRO
    return Acao::ERRO;
}