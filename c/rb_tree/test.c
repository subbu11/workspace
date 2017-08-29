#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "tree.h"

/**
 * RB_INSERT_COLOR ---> key is found in map, but pointer is not found.
 * RB_REMOVE_COLOR ---> key is found in map, but pointer is not found.
 *
 **/

typedef struct Bearer
{
    uint32_t  ebi;
} BearerT;

typedef struct Session
{
   uint32_t  id;
   uint32_t  pdnId;
   uint32_t  imsi;

   BearerT   bearer;
   BearerT*  defaultBearer;
   
   RB_ENTRY (Session)    sessionMapRbtNode; /**< RB Tree Data Structure Node        */
   RB_ENTRY (Session)    sessionImsiMapRbtNode; /**< RB Tree Data Structure Node        */
} SessionT;


static inline int
compareSession(struct Session* a, struct Session* b)
{
    if (a->id > b->id) return 1;
    if (a->id < b->id) return -1;
    if (a->pdnId > b->pdnId) return 1;
    if (a->pdnId < b->pdnId) return -1;
    return 0;
}

static inline int
compareImsiSession(struct Session* a, struct Session* b)
{
    if(a->imsi > b->imsi) return 1;
    if(a->imsi < b->imsi) return -1;

    BearerT* bearerA = a->defaultBearer;
    BearerT* bearerB = b->defaultBearer;

    if (bearerA->ebi > bearerB->ebi) return 1;
    if (bearerA->ebi < bearerB->ebi) return -1;
    return 0;
}

RB_HEAD(SessionMap, Session) sessionMap;
RB_HEAD(SessionImsiMap, Session) sessionImsiMap;

RB_GENERATE(SessionMap, Session, sessionMapRbtNode, compareSession)
RB_GENERATE(SessionImsiMap, Session, sessionImsiMapRbtNode, compareImsiSession)

int RegisterSession(SessionT* pSession, uint32_t id, uint32_t pdnId, uint32_t imsi, uint32_t ebi);
SessionT* FindSession(uint32_t id, uint32_t pdnId);
int DeRegisterSession(SessionT* pSession);

int RegisterSession(SessionT* pSession, uint32_t id, uint32_t pdnId, uint32_t imsi, uint32_t ebi)
{
    SessionT       *pCollision = NULL;

    SessionT sessionKey;
    sessionKey.id       = id;
    sessionKey.pdnId    = pdnId;
    sessionKey.imsi     =  imsi;
    sessionKey.defaultBearer = &sessionKey.bearer;
    (sessionKey.defaultBearer)->ebi = ebi;

    pCollision = RB_FIND(SessionMap, &sessionMap, &sessionKey);
    if(pCollision && (pCollision != pSession))
    {
#if 0
        VCM_LOG_INFO( "Registering New Session '%p'; "
                "Session already exists '%p' for %x:%x",
                pSession, pCollision, id, dpeSessionId2);
#endif

        RB_REMOVE(SessionMap, &sessionMap, pCollision);

        DeRegisterSession(pCollision);
        return RegisterSession(pSession, id,
                pdnId, imsi, ebi);
    }

    pCollision = RB_FIND(SessionImsiMap,
            &sessionImsiMap, &sessionKey);

    if(pCollision && (pCollision != pSession))
    {
#if 0
        VCM_LOG_INFO( "Registering New Session '%p'; Session already "
                "exists '%p' for IMSI EBI Pair ["VCM_IMSI_STR":%u]",
                pSession, pCollision, VCM_IMSI(aImsi), aEbi);
#endif
        RB_REMOVE(SessionImsiMap, &sessionImsiMap, pCollision);

        DeRegisterSession(pCollision);
        return RegisterSession(pSession, id,
                pdnId, imsi, ebi);
    }
    else
    {
#if 0
        VCM_LOG_DEBG("Registering New Session '%p'; No existing "
                "session for - ["VCM_IMSI_STR":%u]",
                pSession, VCM_IMSI(aImsi), aEbi);
#endif
    }

    pSession->defaultBearer = &pSession->bearer;
    pSession->id            = id;
    pSession->pdnId         = pdnId;
    pSession->imsi          = imsi;
    pSession->defaultBearer->ebi = ebi;

#if 0
    VCM_LOG_DEBG( "Registering session with key %08x %08x!",
            pSession->dpeSessionId,
            pSession->dpeSessionId2);
#endif

    pCollision = RB_INSERT(SessionMap, &sessionMap, pSession);
    if(pCollision)
    {
#if 0
        VCM_LOG_ERRO( "User plane flow already exists "
                "for session id %x:%x", (NwU32T)dpeSessionId,
                (NwU32T) dpeSessionId2);
#endif
        return 0;
    }
#if 0
    VCM_LOG_DEBG( "Registering session with key "VCM_IMSI_STR
            ":%u! in IMSI Map", VCM_IMSI(pSession->imsi),
            pEpsBearer->ebi);
#endif
    pCollision = RB_INSERT(SessionImsiMap,
            &sessionImsiMap, pSession);
    if(pCollision)
    {
#if 0
        VCM_LOG_ERRO( "User plane flow already exists for "VCM_IMSI_STR
                ":%u - Removing from session map!",
                VCM_IMSI(pSession->imsi), pEpsBearer->ebi);
#endif
        RB_REMOVE(SessionMap, &sessionMap, pSession);
#if 0
        VCM_LOG_ERRO( "User plane flow removed from session "
                "map due to IMSI collision for ref-Id %x:%x",
                (NwU32T)dpeSessionId, dpeSessionId2);
#endif
        return 0;
    }
#if 0
    VCM_LOG_DEBG("Session '%p' registration completed successfully "
            "for ["VCM_IMSI_STR":%u]",
            pSession, VCM_IMSI(pSession->imsi),
            VCM_DPE_SESSION_GET_BEARER(pSession,
                pSession->defaultBearerIndex)->ebi);
#endif

    return 1;
}

SessionT* FindSession(uint32_t id, uint32_t pdnId)
{
    SessionT       *pSession;

    SessionT       sessionKey;
    sessionKey.id       = id;
    sessionKey.pdnId    = pdnId;
    
    pSession = RB_FIND(SessionMap, &sessionMap, &sessionKey);
    
    return pSession;
}

int DeRegisterSession(SessionT* pSession)
{
    if( pSession == RB_FIND(SessionMap, &sessionMap, pSession) )
    {
        RB_REMOVE(SessionMap, &sessionMap, pSession);
    }

    if( pSession == RB_FIND(SessionImsiMap, &sessionImsiMap, pSession) )
    {
        RB_REMOVE(SessionImsiMap, &sessionImsiMap, pSession);
    }

    return 1;
}

int main()
{
#if 0
    SessionT i1 = {0};
    i1.key = 10;
    printf("node == %08X\n", &i1);

    printf("INSERTING i1=%08X", &i1);
    SessionT* check = RB_INSERT(SessionMap, &map, &i1);

    if(check == NULL)
    {
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }
    printf("\n\n\n\n");
    
    SessionT i2 = {0};
    i2.key = 10;
    printf("node == %08X\n", &i2);

    printf("INSERTING i2=%08X", &i2);
    check = RB_INSERT(SessionMap, &map, &i2);

    if(check == NULL)
    {
        printf("success\n");
    }
    else
    {
        printf("check == %08X\n", check);
        printf("failed\n");
    }
    printf("\n\n\n\n");
    
    printf("REMOVING i1=%08X", &i1);
    check = RB_REMOVE(SessionMap, &map, &i1);
    if(check != NULL)
    {
        printf("check == %08X\n", check);
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }
    printf("\n\n\n\n");

    check = RB_FIND(SessionMap, &map, &i1);
    if(check)
    {
        printf("FOUND check=%08X\n", check);
    }
    else
    {
        printf("NOT FOUND %08X\n", check);
    }

    check = RB_FIND(SessionMap, &map, &i2);
    if(check)
    {
        printf("FOUND check=%08X\n", check);
    }
    else
    {
        printf("NOT FOUND %08X\n", check);
    }

    printf("REMOVING i1=%08X", &i1);
    check = NULL;
    check = RB_REMOVE(SessionMap, &map, &i1);
    if(check != NULL)
    {
        printf("check == %08X\n", check);
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }
    printf("\n\n\n\n");

    printf("REMOVING i2=%08X", &i2);
    check = NULL;
    check = RB_REMOVE(SessionMap, &map, &i2);
    if(check != NULL)
    {
        printf("check == %08X\n", check);
        printf("success\n");
    }
    else
    {
        printf("failed\n");
    }
    printf("\n\n\n\n");
#endif
}
