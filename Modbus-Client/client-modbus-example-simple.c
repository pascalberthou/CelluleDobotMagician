#include <stdio.h>
#include <modbus.h>
#include <api-modbus-dobot.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

#define SERVER_IP "169.254.36.66"
#define SERVER_PORT 502

void fbreak(int signum)
{
    printf("Fermeture de la connexion\n");
    reset_comm();
    exit(0);
}

modbus_t *ctx;

int init_comm(char *ip,int port)
{
     // Création du contexte Modbus TCP
    ctx = modbus_new_tcp(ip, port);
    if (ctx == NULL) {
        fprintf(stderr, "Erreur lors de la création du contexte Modbus\n");
        return -1;
    }

    // Connexion au serveur Modbus TCP (Arduino)
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Impossible de se connecter à %s:%d\n", SERVER_IP, SERVER_PORT);
        modbus_free(ctx);
        return -1;
    }
    return(1);
}

/**
 * @brief Lit la valeur d'un bit donné à l'adresse indiquee
 *
 * La fonction prend l'adresse de du bit 
 * et retourne -1 si une erreur est survenue lors de la lecture., 
 * sinon elle retourne la valeur du bit.
 *
 * @param input_bit l'adresse du bit à lire
 * @return la valeur du bit (TRUE ou FALSE) ou -1 si une erreur est survenue
 */
int modbus_read_bin(int input_bit)
{
    uint8_t val;
    if (modbus_read_input_bits(ctx,INPUT_I,1,&val))
        return(val);
    else
        return -1;
}   

/**
 * @brief Ecrit la valeur d'un bit donné à l'adresse indiquee
 *
 * La fonction prend l'adresse de du bit et la valeur 
 * et retourne -1 si une erreur est survenue lors de l'ecriture., 
 * sinon elle retourne 1.
 *
 * @param input_bit l'adresse du bit à ecrire et sa valeur
 * @return 1 si l'ecriture s'est bien passé et -1 si une erreur est survenue
 */
int modbus_write_bin(int output_bit, int value)
{
    // Ecrire une valeur dans un bit Modbus (bit 0)
    if (modbus_write_bit(ctx, output_bit, value) == -1) {
        fprintf(stderr, "Erreur lors de l'écriture du bit\n");
        return -1;
    } else {
        return 1;
    }
}

/**
 * @brief Lit une valeur entiere à l'adresse indiquee
 *
 * La fonction prend l'adresse du registre 
 * et retourne -1 si une erreur est survenue lors de la lecture., 
 * sinon elle retourne la valeur du registre.
 *
 * @param input_bit l'adresse du registre à lire
 * @return la valeur du registre ou -1 si une erreur est survenue
 */
 uint16_t modbus_read_regs(int input_reg)
{
    uint16_t reg;  // Tableau pour stocker les registres lus
 // Lire un registre Modbus (registre 0)
    if (modbus_read_registers(ctx, input_reg, 1, &reg) == -1) {
        fprintf(stderr, "Erreur lors de la lecture du registre\n");
        return -1;   
    } else {
        return reg;
        
    }
}

/**
 * @brief Ecrit une valeur entiere à l'adresse indiquee
 *
 * La fonction prend l'adresse du registre et la valeur a ecrite 
 * et retourne -1 si une erreur est survenue lors de l'ecriture., 
 * sinon elle retourne 1.
 *
 * @param input_bit l'adresse du registre à lire
 * @return la valeur du registre ou -1 si une erreur est survenue
 */
int modbus_write_regs(int output_reg, int value)
{
    // Ecrire une valeur dans un registre Modbus (registre 0)
    if (modbus_write_register(ctx, output_reg, value) == -1) {
        fprintf(stderr, "Erreur lors de l'écriture du registre\n");
        return -1;
    } else {
        return 1;
    }
}

void reset_comm()
{
    // Fermer la connexion et libérer les ressources
    modbus_close(ctx);
    modbus_free(ctx);
}

int main() {
 
    int val;  // Tableau pour stocker les registres lus
    int menu=0;

    signal(SIGINT, &fbreak); // break pour la fermeture de connexion
    init_comm(SERVER_IP,SERVER_PORT);
    printf("Connexion réussie à l'Arduino Modbus TCP\n");


    while(1)
    {

        printf("Menu test Modbus\n");
        printf("1. Lecture  bits I() \n");
        printf("2. Ecriture bits StartTi(1) \n");
        printf("3. Ecriture bits StopTi(1) \n");
        scanf("%d",&menu);

    switch(menu)
    {
        case 1: 
                val=I();
                if (val!=-1) {
                    printf("Valeur du bit %d : %u\n",INPUT_I,val);
                } else {
                    printf("Erreur lors de la lecture du bit\n");
                }
                break;
        case 2 : 
            // printf("2. Lecture / Ecriture registres\n");
            // Tests Lecture / Ecriture bits
            // Ecrit la valeur d'un bit
                // Lit la cette valeur depuis le serveur modbus
                if (StartTi(1) == -1) {
                    printf("Erreur lors de l'écriture du bit\n");
                } else {
                    printf("Ecriture du bit %d réussie\n",COIL_StopTi);
                }
                break;
        case 3 :
                if (StopTi(1) == -1) {
                    printf("Erreur lors de l'écriture du bit\n");
                } else {
                    printf("Ecriture du bit %d réussie\n",COIL_StopTi);
                }
                break;
        default : 
                printf("Erreur de saisie\n");
                break;
    }
 
   /* 
*/
    // Tests Lecture / Ecriture registres
    // Ecrit la valeur d'un registre
    // Lit la cette valeur depuis le serveur modbus
    /*if (modbus_write_regs(COIL_StartTi, 1) == -1) {
        printf("Erreur lors de l'écriture du registre\n");
    } else {
        printf("Ecriture du registre %d réussie\n",COIL_StartTi);
    }
    val=C1(); 
    printf("Valeur du registre %d : %d\n",INPUT_C1,val);
*/
    }
    reset_comm();

    return 0;
}