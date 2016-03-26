#include "MPC.H"

/*--------------------------------------------------------------------------*/

INT8U   mode_late,mode_long,mode_vert,mode_rota,
        token_late,token_long,token_vert,token_rota;

INT16S  on_sky, on_takeoff,takeoff_pre;
int     tag_home, tag_land, tag_endwp;


/*--------------------------------------------------------------------------*/


void LATE(void)          //左右模态
{
    if (token_late==TOKEN_TurnLeft) {

        mode_late = PW_LateLeft;
        mode_long=PW_LongNone;
        gama_cmd = PW_GamaLeft;
        mode_vert=PW_VertNone;
        mode_rota = PW_RotaNone;
        mode_guid=0;
        theta_cmd=0;
        //psi_cmd=ac_psi;
        //height_cmd=ac_height;
        BackupRPVs();
        token_late=TOKEN_LateNone;
        CreatTask(LATE,Timer50ms);
    }

     else if (token_late==TOKEN_TurnRight) {

        mode_late = PW_LateRight;
        mode_long=PW_LongNone;
        mode_vert=PW_VertNone;
        mode_rota = PW_RotaNone;
        mode_guid=0;
        gama_cmd = PW_GamaRight;
        theta_cmd=0;
        //psi_cmd=ac_psi;
        //height_cmd=ac_height;
        BackupRPVs();
        token_late=TOKEN_LateNone;
        CreatTask(LATE,Timer50ms);
    }

    else  {
        CreatTask(LATE,Timer50ms);
    }
}

void LONG(void)           //前后模态
{
    if (token_long==TOKEN_TurnForth) {

                mode_long = PW_LongForth;
                mode_late=PW_LateNone;
                mode_vert=PW_VertNone;
                mode_rota = PW_RotaNone;
                mode_guid=0;
                theta_cmd = PW_ThetaForth;
                gama_cmd=0;
                //psi_cmd=ac_psi;
                //height_cmd=ac_height;
                BackupRPVs();
                token_long=TOKEN_LongNone;
                CreatTask(LONG,Timer50ms);

            }

     else if (token_long==TOKEN_TurnBack) {

                mode_long = PW_LongBack;
                mode_late=PW_LateNone;
                mode_vert=PW_VertNone;
                mode_guid=0;
                mode_rota = PW_RotaNone;
                theta_cmd = PW_ThetaBack;
                gama_cmd=0;
                //psi_cmd=ac_psi;
                //height_cmd=ac_height;
                BackupRPVs();
                token_long=TOKEN_LongNone;
                CreatTask(LONG,Timer50ms);

            }

     else   {
                CreatTask(LONG,Timer50ms);
            }
}



void VERT(void)          //上下模态
{

    if (token_vert==TOKEN_TurnUp) {

                mode_vert = PW_VertUp;
                mode_rota = PW_RotaNone;
                mode_late=PW_LateNone;
                mode_long=PW_LongNone;
                mode_guid=0;
                theta_cmd=0;
                gama_cmd=0;
                psi_cmd=ac_psi;
                BackupRPVs();
                token_vert=TOKEN_VertNone;
                CreatTask(VERT,Timer50ms);

            }

     else if (token_vert==TOKEN_TurnDown) {

                mode_vert = PW_VertDown;
                mode_rota = PW_RotaNone;
                mode_late=PW_LateNone;
                mode_long=PW_LongNone;
                mode_guid=0;
                theta_cmd=0;
                gama_cmd=0;
                psi_cmd=ac_psi;
                BackupRPVs();
                token_vert=TOKEN_VertNone;
                CreatTask(VERT,Timer50ms);

            }

     else   {
                CreatTask(VERT,Timer50ms);
            }

}



void ROTA(void)            //旋转模态
{
    if (token_rota == TOKEN_RotaLeft) {

                mode_rota = PW_RotaLeft;
                mode_late=PW_LateNone;
                mode_vert=PW_VertNone;
                mode_long=PW_LongNone;
                mode_guid=0;
                theta_cmd=0;
                gama_cmd=0;
                height_cmd=ac_height;
                BackupRPVs();
                token_rota=TOKEN_RotaNone;
                CreatTask(ROTA,Timer50ms);

            }

    else if (token_rota==TOKEN_RotaRight) {

                mode_rota = PW_RotaRight;
                mode_late=PW_LateNone;
                mode_vert=PW_VertNone;
                mode_long=PW_LongNone;
                mode_guid=0;
                theta_cmd=0;
                gama_cmd=0;
                height_cmd=ac_height;
                BackupRPVs();
                token_rota=TOKEN_RotaNone;
                CreatTask(ROTA,Timer50ms);

            }

     else   {
                CreatTask(ROTA,Timer50ms);
            }
}
