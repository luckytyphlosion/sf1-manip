#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned char u8;

typedef struct {
    uint index;
    uint chip_trader_optimize;
    uint twist_count;
    uint state[624];
} RNG;

RNG * rng_instantiate(uint chip_trader_optimize);
void rng_init(RNG * rng, uint seed);
uint rng_next(RNG * rng);
void rng_twist(RNG * rng);

#define SetBit(A,k)     ( A[(k/32)] |= (1 << (k%32)) )
#define ClearBit(A,k)   ( A[(k/32)] &= ~(1 << (k%32)) )
#define TestBit(A,k)    ( A[(k/32)] & (1 << (k%32)) )

uint * found_seeds = NULL;

const char * card_names[] = {
    "Cannon",
    "PlusCannon",
    "HevyCannon",
    "PlasmaGun1",
    "PlasmaGun2",
    "PlasmaGun3",
    "Gatling1",
    "Gatling2",
    "Gatling3",
    "AirSpread",
    "RdrMissil1",
    "RdrMissil2",
    "RdrMissil3",
    "HeatBall1",
    "HeatBall2",
    "HeatBall3",
    "IceMeteor1",
    "IceMeteor2",
    "IceMeteor3",
    "StunNukle",
    "PoisNukle",
    "FreezNukle",
    "Sword",
    "WideSword",
    "LongSword",
    "BlazngEdge",
    "TidalEdge",
    "StrikeEdge",
    "ArboEdge",
    "BreakSabre",
    "GrndWave1",
    "GrndWave2",
    "GrndWave3",
    "JetAttack1",
    "JetAttack2",
    "JetAttack3",
    "PowerBomb1",
    "PowerBomb2",
    "PowerBomb3",
    "GhstPulse1",
    "GhstPulse2",
    "GhstPulse3",
    "FireRing1",
    "FireRing2",
    "FireRing3",
    "TimeBomb1",
    "TimeBomb2",
    "TimeBomb3",
    "FireBzook1",
    "FireBzook2",
    "FireBzook3",
    "TailBurnr1",
    "TailBurnr2",
    "TailBurnr3",
    "WideWave1",
    "WideWave2",
    "WideWave3",
    "ChainBubl1",
    "ChainBubl2",
    "ChainBubl3",
    "GreenInk",
    "BlueInk",
    "PurpleInk",
    "StikyRain1",
    "StikyRain2",
    "StikyRain3",
    "CloudShot1",
    "CloudShot2",
    "CloudShot3",
    "ThndrBall1",
    "ThndrBall2",
    "ThndrBall3",
    "VolticEye1",
    "VolticEye2",
    "VolticEye3",
    "FlickrKck1",
    "FlickrKck2",
    "FlickrKck3",
    "JumboHmmr1",
    "JumboHmmr2",
    "JumboHmmr3",
    "MopLance1",
    "MopLance2",
    "MopLance3",
    "Fokx-Fu1",
    "Fokx-Fu2",
    "Fokx-Fu3",
    "VulcnSeed1",
    "VulcnSeed2",
    "VulcnSeed3",
    "BraveSwrd1",
    "BraveSwrd2",
    "BraveSwrd3",
    "JunkCube1",
    "JunkCube2",
    "JunkCube3",
    "SyncHook1",
    "SyncHook2",
    "SyncHook3",
    "PowerSong",
    "QuakeSong",
    "TripSong",
    "MoaiFall1",
    "MoaiFall2",
    "MoaiFall3",
    "BigAx1",
    "BigAx2",
    "BigAx3",
    "MagiCrysl1",
    "MagiCrysl2",
    "MagiCrysl3",
    "BlackHole1",
    "BlackHole2",
    "BlackHole3",
    "BrsrkSwrd1",
    "BrsrkSwrd2",
    "BrsrkSwrd3",
    "GreenBurst",
    "IceBurst",
    "PoisBurst",
    "TyphnDance",
    "JamminPnch",
    "JamMachGun",
    "Whistle",
    "Bombalizer",
    "AntiSword",
    "Recover10",
    "Recover30",
    "Recover50",
    "Recover80",
    "Recover120",
    "Recover150",
    "Recover200",
    "Recover300",
    "Barrier",
    "Barrier100",
    "Barrier200",
    "Aura",
    "Invisible",
    "SpiritFury",
    "PoisnApple",
    "DoublCross",
    "GigaMine",
    "GrassStage",
    "IceStage",
    "GraviStage",
    "GNullStage",
    "HolyPanel",
    "ParlyzPlus",
    "Attack+10",
    "TaurusFire",
    "TaursFireEX",
    "TaursFireSP",
    "CygnusWing",
    "CygnsWingEX",
    "CygnsWingSP",
    "HarpNote",
    "HarpNoteEX",
    "HarpNoteSP",
    "LibraScals",
    "LibrScalsEX",
    "LibrScalsSP",
    "QnOphiuca",
    "QnOphiucaEX",
    "QnOphiucaSP",
    "GeminSpark",
    "GemnSpkEX",
    "GemnSpkSP",
    "CancrBuble",
    "CancrBublEX",
    "CancrBublSP",
    "WolfWoods",
    "WolfWoodsEX",
    "WolfWoodsSP",
    "CrwnThundr",
    "CrwnThndrEX",
    "CrwnThndrSP",
    "PegasusMgc",
    "PegasuMgcEX",
    "PegasuMgcSP",
    "LeoKingdom",
    "LeoKingdmEX",
    "LeoKingdmSP",
    "DragonSky",
    "DragonSkyEX",
    "DragonSkySP"
};

typedef enum {
    Cannon,
    PlusCannon,
    HevyCannon,
    PlasmaGun1,
    PlasmaGun2,
    PlasmaGun3,
    Gatling1,
    Gatling2,
    Gatling3,
    AirSpread,
    RdrMissil1,
    RdrMissil2,
    RdrMissil3,
    HeatBall1,
    HeatBall2,
    HeatBall3,
    IceMeteor1,
    IceMeteor2,
    IceMeteor3,
    StunNukle,
    PoisNukle,
    FreezNukle,
    Sword,
    WideSword,
    LongSword,
    BlazngEdge,
    TidalEdge,
    StrikeEdge,
    ArboEdge,
    BreakSabre,
    GrndWave1,
    GrndWave2,
    GrndWave3,
    JetAttack1,
    JetAttack2,
    JetAttack3,
    PowerBomb1,
    PowerBomb2,
    PowerBomb3,
    GhstPulse1,
    GhstPulse2,
    GhstPulse3,
    FireRing1,
    FireRing2,
    FireRing3,
    TimeBomb1,
    TimeBomb2,
    TimeBomb3,
    FireBzook1,
    FireBzook2,
    FireBzook3,
    TailBurnr1,
    TailBurnr2,
    TailBurnr3,
    WideWave1,
    WideWave2,
    WideWave3,
    ChainBubl1,
    ChainBubl2,
    ChainBubl3,
    GreenInk,
    BlueInk,
    PurpleInk,
    StikyRain1,
    StikyRain2,
    StikyRain3,
    CloudShot1,
    CloudShot2,
    CloudShot3,
    ThndrBall1,
    ThndrBall2,
    ThndrBall3,
    VolticEye1,
    VolticEye2,
    VolticEye3,
    FlickrKck1,
    FlickrKck2,
    FlickrKck3,
    JumboHmmr1,
    JumboHmmr2,
    JumboHmmr3,
    MopLance1,
    MopLance2,
    MopLance3,
    Fokx_Fu1,
    Fokx_Fu2,
    Fokx_Fu3,
    VulcnSeed1,
    VulcnSeed2,
    VulcnSeed3,
    BraveSwrd1,
    BraveSwrd2,
    BraveSwrd3,
    JunkCube1,
    JunkCube2,
    JunkCube3,
    SyncHook1,
    SyncHook2,
    SyncHook3,
    PowerSong,
    QuakeSong,
    TripSong,
    MoaiFall1,
    MoaiFall2,
    MoaiFall3,
    BigAx1,
    BigAx2,
    BigAx3,
    MagiCrysl1,
    MagiCrysl2,
    MagiCrysl3,
    BlackHole1,
    BlackHole2,
    BlackHole3,
    BrsrkSwrd1,
    BrsrkSwrd2,
    BrsrkSwrd3,
    GreenBurst,
    IceBurst,
    PoisBurst,
    TyphnDance,
    JamminPnch,
    JamMachGun,
    Whistle,
    Bombalizer,
    AntiSword,
    Recover10,
    Recover30,
    Recover50,
    Recover80,
    Recover120,
    Recover150,
    Recover200,
    Recover300,
    Barrier,
    Barrier100,
    Barrier200,
    Aura,
    Invisible,
    SpiritFury,
    PoisnApple,
    DoublCross,
    GigaMine,
    GrassStage,
    IceStage,
    GraviStage,
    GNullStage,
    HolyPanel,
    ParlyzPlus,
    Attack_10,
    TaurusFire,
    TaursFireEX,
    TaursFireSP,
    CygnusWing,
    CygnsWingEX,
    CygnsWingSP,
    HarpNote,
    HarpNoteEX,
    HarpNoteSP,
    LibraScals,
    LibrScalsEX,
    LibrScalsSP,
    QnOphiuca,
    QnOphiucaEX,
    QnOphiucaSP,
    GeminSpark,
    GemnSpkEX,
    GemnSpkSP,
    CancrBuble,
    CancrBublEX,
    CancrBublSP,
    WolfWoods,
    WolfWoodsEX,
    WolfWoodsSP,
    CrwnThundr,
    CrwnThndrEX,
    CrwnThndrSP,
    PegasusMgc,
    PegasuMgcEX,
    PegasuMgcSP,
    LeoKingdom,
    LeoKingdmEX,
    LeoKingdmSP,
    DragonSky,
    DragonSkyEX,
    DragonSkySP
} card_type;

const card_type amaken_lists[][65] = {
    {8, TaursFireSP, CygnsWingSP, HarpNoteSP, LibrScalsSP, QnOphiucaSP, GemnSpkSP, GigaMine, BreakSabre},
    {16, TaursFireEX, CygnsWingEX, HarpNoteEX, LibrScalsEX, QnOphiucaEX, GemnSpkEX, TyphnDance, TyphnDance, JamminPnch, JamMachGun, HolyPanel, HolyPanel, Aura, Aura, Barrier200, Barrier200},
    {16, TaurusFire, CygnusWing, HarpNote, LibraScals, QnOphiuca, GeminSpark, DoublCross, Recover300, Barrier100, GreenBurst, GreenBurst, IceBurst, IceBurst, PoisBurst, SpiritFury, PoisnApple},
    {32, BrsrkSwrd3, Fokx_Fu3, VulcnSeed3, JunkCube3, MoaiFall3, BigAx3, MagiCrysl3, BlackHole3, Bombalizer, AntiSword, BlazngEdge, TidalEdge, StrikeEdge, ArboEdge, StunNukle, PoisNukle, FreezNukle, RdrMissil3, IceMeteor3, Gatling3, PlasmaGun3, Recover200, HevyCannon, FlickrKck3, MopLance3, BraveSwrd3, SyncHook3, StikyRain3, CloudShot3, ThndrBall3, JumboHmmr3, VolticEye3},
    {32, HeatBall3, PlasmaGun2, Gatling2, RdrMissil2, HeatBall2, IceMeteor2, Whistle, Whistle, GrndWave3, JetAttack3, PowerBomb3, GhstPulse3, FireRing3, TimeBomb3, FireBzook3, TailBurnr3, WideWave3, ChainBubl3, Recover120, Recover120, Recover150, BrsrkSwrd2, BlackHole2, MagiCrysl2, BigAx2, MoaiFall2, TripSong, VolticEye2, JunkCube2, VulcnSeed2, Fokx_Fu2, Invisible},
    {64, GrndWave2, JetAttack2, PowerBomb2, GhstPulse2, FireRing2, TimeBomb2, FireBzook2, TailBurnr2, WideWave2, ChainBubl2, StikyRain2, CloudShot2, ThndrBall2, SyncHook2, FlickrKck2, JumboHmmr2, MopLance2, VolticEye1, VolticEye1, Fokx_Fu1, Fokx_Fu1, VulcnSeed1, VulcnSeed1, BraveSwrd2, BraveSwrd2, JunkCube1, JunkCube1, PowerSong, PowerSong, QuakeSong, QuakeSong, BigAx1, BigAx1, MagiCrysl1, MagiCrysl1, BlackHole1, BlackHole1, BrsrkSwrd1, BrsrkSwrd1, GreenInk, GreenInk, BlueInk, BlueInk, PurpleInk, PurpleInk, Recover80, Recover80, PlusCannon, PlusCannon, AirSpread, AirSpread, Sword, WideSword, LongSword, GrassStage, GrassStage, IceStage, IceStage, GraviStage, GraviStage, GNullStage, GNullStage, ParlyzPlus, Attack_10}
};

RNG * rng_instantiate(uint chip_trader_optimize) {
    RNG * rng = malloc(sizeof(RNG));
    rng->chip_trader_optimize = chip_trader_optimize;
    rng_init(rng, 4357);
    return rng;
}

void rng_init(RNG * rng, uint seed) {
    uint next = 0;

    if (rng->chip_trader_optimize) {
        for (int i = 0; i < 4; i++) {
            next = 69069 * seed + 1;
            rng->state[i] = (seed & 0xFFFF0000) | ((next & 0xFFFF0000) >> 16);
            seed = 69069 * next + 1;
        }
        // magic
        // uses a**n*seed+b*(a**n-1)/(a-1), the formula for advancing an LCG n times
        seed = (2515655785 * seed + 3424356862);

        for (int i = 397; i < 400; i++) {
            next = 69069 * seed + 1;
            rng->state[i] = (seed & 0xFFFF0000) | ((next & 0xFFFF0000) >> 16);
            seed = 69069 * next + 1;
        }
    } else {
        for (int i = 0; i < 624; i++) {
            next = 69069 * seed + 1;
            rng->state[i] = (seed & 0xFFFF0000) | ((next & 0xFFFF0000) >> 16);
            seed = 69069 * next + 1;
        }
    }
    rng->index = 624;
    rng->twist_count = 0;
}

uint rng_next(RNG * rng) {
    if (rng->index >= 624) {
        rng_twist(rng);
    }
    
    uint seed = rng->state[rng->index++];
    seed ^= (seed >> 11);
    seed ^= (seed <<  7) & 0x9D2C5680;
    seed ^= (seed << 15) & 0xEFC60000;
    seed ^= (seed >> 18);

    return seed;
}

void rng_twist(RNG * rng) {
    if (rng->index == 625) {
        rng_init(rng, 4357);
    }
    
    uint seed, xor;
    
    if (rng->chip_trader_optimize) {
        for (int i = 0; i < 3; i++) {
            seed = (rng->state[i] & 0x80000000) | (rng->state[i + 1] & 0x7FFFFFFF);
            xor = (seed & 1) != 0 ? 0x9908B0DF : 0;
            seed = (seed >> 1) & 0x7FFFFFFF;
            rng->state[i] = seed ^ rng->state[i + 397] ^ xor;
        }
    } else {
        for (int i = 0; i < 227; i++) {
            seed = (rng->state[i] & 0x80000000) | (rng->state[i + 1] & 0x7FFFFFFF);
            xor = (seed & 1) != 0 ? 0x9908B0DF : 0;
            seed = (seed >> 1) & 0x7FFFFFFF;
            rng->state[i] = seed ^ rng->state[i + 397] ^ xor;
        }
        for (int i = 227; i < 623; i++) {
            seed = (rng->state[i] & 0x80000000) | (rng->state[i + 1] & 0x7FFFFFFF);
            xor = (seed & 1) != 0 ? 0x9908B0DF : 0;
            seed = (seed >> 1) & 0x7FFFFFFF;
            rng->state[i] = seed ^ rng->state[i - 227] ^ xor;
        }
        {
            seed = (rng->state[623] & 0x80000000) | (rng->state[0] & 0x7FFFFFFF);
            xor = (seed & 1) != 0 ? 0x9908B0DF : 0;
            seed = (seed >> 1) & 0x7FFFFFFF;
            rng->state[623] = seed ^ rng->state[396] ^ xor;
        }
    }
    rng->twist_count++;
    rng->index = 0;
}

void rng_set_chip_trader_optimize(RNG * rng, uint chip_trader_optimize) {
    rng->chip_trader_optimize = chip_trader_optimize;
}

// 614 + 10 = 624
// 614 + 11 = 625 = 1
//
void rng_jump_ahead(RNG * rng, uint amount) {
    while (rng->index + amount > 624) {
        amount = amount - (624 - rng->index);
        rng_twist(rng);
    }
    rng->index += amount;
}

int find_one_seed_period(void) {
    RNG * rng = rng_instantiate(TRUE);
    uint cur_seed = 0xb704d97d;
    rng_init(rng, cur_seed);
    found_seeds = calloc(1, 0x20000000);

    uint i;

    for (i = 0; i < 0xffffffff; i++) {
        if (TestBit(found_seeds, cur_seed)) {
            break;
        }
        SetBit(found_seeds, cur_seed);
        rng_next(rng);
        rng_next(rng);
        cur_seed = rng_next(rng);
        rng_init(rng, cur_seed);
        if (i % 10000 == 0) {
            printf("i: %d\n", i);
        }
        //printf("cur seed: %08x\n", cur_seed);
    }
    printf("cur_seed: %08x, period: %d\n", cur_seed, i + 1);
}

void find_all_periods(void) {
    RNG * rng = rng_instantiate(TRUE);
    found_seeds = calloc(1, 0x20000000);

    uint cur_seed = 0x12bf0900;
    uint rng_index;
    uint num_seeds = 0;

    while (TRUE) {
        uint old_seed = cur_seed;
        rng_init(rng, cur_seed);
        uint debug_count = 0;
        for (rng_index = 0; rng_index < 0xffffffff; rng_index++) {
            if (TestBit(found_seeds, cur_seed)) {
                printf("start_seed: %08x, repeat_seed: %08x, period: %d\n", old_seed, cur_seed, rng_index + 1);
                break;
            }
            SetBit(found_seeds, cur_seed);
            if (FALSE) {
                printf("seed1: %08x\n", rng_next(rng));
                printf("seed2: %08x\n", rng_next(rng));
                cur_seed = rng_next(rng);
                printf("seed3: %08x\n", cur_seed);
            } else {
                rng_next(rng);
                rng_next(rng);
                cur_seed = rng_next(rng);
            }
            rng_init(rng, cur_seed);
            debug_count++;
            
        }
        num_seeds += rng_index + 1;

        cur_seed = old_seed;
        while (TestBit(found_seeds, cur_seed)) {
            if (cur_seed >= (0x12bf0900 + 86541)) {
                goto processed_all_seeds;
            }
            cur_seed++;
        }
    }
processed_all_seeds:
    printf("num_seeds: %d\n", num_seeds);

}

const card_type good_cards[] = {
    BrsrkSwrd3,
    JunkCube3,
    BigAx3,
    MagiCrysl3,
    BlackHole3,
    BlackHole2,
    MagiCrysl2,
    VolticEye2,
    Fokx_Fu3,
    BrsrkSwrd2
};

#define LEN(x)  (sizeof(x) / sizeof((x)[0]))

void reset_good_card_bool_array(unsigned char * good_card_bool_array);

unsigned char * initialize_good_card_bool_array(void) {
    unsigned char * good_card_bool_array = calloc(1, DragonSkySP + 1);
    reset_good_card_bool_array(good_card_bool_array);
    return good_card_bool_array;
}

void reset_good_card_bool_array(unsigned char * good_card_bool_array) {
    for (int i = 0; i < LEN(good_cards); i++) {
        good_card_bool_array[good_cards[i]] = TRUE;
    }
}

card_type simulate_card_trader_roll(RNG * rng, const card_type card_list_list[][65]) {
    uint card_list_list_index = rng_next(rng) & 0x3f;
    const card_type * card_list;
    if (card_list_list_index == 0) {
        card_list = card_list_list[0];
    } else if (card_list_list_index <= 6) {
        card_list = card_list_list[1];
    } else if (card_list_list_index <= 14) {
        card_list = card_list_list[2];
    } else if (card_list_list_index <= 24) {
        card_list = card_list_list[3];
    } else if (card_list_list_index <= 40) {
        card_list = card_list_list[4];
    } else {
        card_list = card_list_list[5];
    }

    uint card_list_index = (rng_next(rng) & (card_list[0] - 1)) + 1;
    rng_init(rng, rng_next(rng));
    return card_list[card_list_index];
}

void find_good_trader_lists(const card_type card_list_list[][65]) {
    RNG * rng = rng_instantiate(TRUE);
    unsigned char * good_card_bool_array = initialize_good_card_bool_array();

    ulong cur_seed = 0x12bf0900;
    uint best_seed = cur_seed;
    uint best_seed_num_cards = 0;
    uint rng_index;
    uint num_seeds = 0;

    for (; cur_seed <= (0x12bf0900 + 86541); cur_seed++) {
        uint cur_seed_start = cur_seed;
        uint cur_seed_num_cards = 0;
        rng_init(rng, cur_seed);
        for (rng_index = 0; rng_index < 15; rng_index++) {
            card_type card = simulate_card_trader_roll(rng, card_list_list);
            if (good_card_bool_array[card]) {
                good_card_bool_array[card] = FALSE;
                //printf("%s\n", card_names[card]);
                cur_seed_num_cards++;
            }
        }

        if (cur_seed % 1000000 == 0) {
            printf("cur_seed: %08x\n", cur_seed);
        }

        if (cur_seed_num_cards > best_seed_num_cards) {
            best_seed_num_cards = cur_seed_num_cards;
            best_seed = cur_seed_start;
        }

        if (cur_seed_num_cards != 0) {
            reset_good_card_bool_array(good_card_bool_array);
        }
    }

    rng_init(rng, best_seed);
    printf("seed: %08x, num_cards: %d\n", best_seed, best_seed_num_cards);
    for (rng_index = 0; rng_index < 15; rng_index++) {
        card_type card = simulate_card_trader_roll(rng, card_list_list);
        printf("%s, ", card_names[card]);
    }
    printf("\n");
}


void get_auto_favourite_cards(RNG * rng, uint * slot_indices) {
    for (int i = 0; i < 6; i++) {
        uint cur_slot = (rng_next(rng) >> 1) % 30;
        for (int j = 0; j < i; j++) {
            if (cur_slot == slot_indices[j]) {
                cur_slot = (cur_slot + 1) % 30;
            }
        }
        slot_indices[i] = cur_slot;
    }
    for (int i = 1; i < 6; i++) {
        for (int j = i; j > 0 && (slot_indices[j - 1] > slot_indices[j]); j--) {
            uint temp = slot_indices[j];
            slot_indices[j] = slot_indices[j - 1];
            slot_indices[j - 1] = temp;
        }
    }
}

#define MACADDR_U32 0x6fbf0900
#define NUM_TRADER_ATTEMPTS 15

typedef struct {
    uint seed;
    uint index;
} seed_skip;

// 0x12bf0900
void find_actual_good_trader_lists(const card_type card_list_list[][65]) {
    RNG * rng_primary = rng_instantiate(FALSE);
    RNG * rng_trader = rng_instantiate(TRUE);
    unsigned char * good_card_bool_array = initialize_good_card_bool_array();

    ulong cur_seed = MACADDR_U32;
    uint best_seed = cur_seed;
    uint best_seed_index = 0;
    uint best_seed_num_cards = 0;
    uint rng_index;
    uint num_seeds = 0;

    uint slot_indices[6];
    
    seed_skip seeds_to_skip[] = {
        //{.seed = 0x6fbf62eb, .index = 493}
    };

    for (; cur_seed <= (MACADDR_U32 + 86541); cur_seed++) {
        uint cur_seed_start = cur_seed;
        
        rng_init(rng_primary, cur_seed);
        rng_twist(rng_primary);
        
        if (cur_seed % 1000 == 0) {
            printf("cur_seed: %08x\n", cur_seed);
        }

        for (rng_primary->index = 0xad; rng_primary->index < 624; rng_primary->index += 3 /* actually += 4, but ++ happens in rng_next()*/) {
            uint skip_this_seed_index = FALSE;
            for (int i = 0; i < LEN(seeds_to_skip); i++) {
                if (cur_seed == seeds_to_skip[i].seed && rng_primary->index == seeds_to_skip[i].index) {
                    rng_primary->index++;
                    skip_this_seed_index = TRUE;
                    break;
                }
            }

            if (skip_this_seed_index) {
                continue;
            }

            uint cur_seed_start = rng_next(rng_primary);
            uint cur_seed_num_cards = 0;
            rng_init(rng_trader, cur_seed_start);
            for (rng_index = 0; rng_index < NUM_TRADER_ATTEMPTS; rng_index++) {
                card_type card = simulate_card_trader_roll(rng_trader, card_list_list);

                if (good_card_bool_array[card]) {
                    good_card_bool_array[card] = FALSE;
                    cur_seed_num_cards++;
                }
            }

            if (cur_seed_num_cards > best_seed_num_cards) {
                best_seed_num_cards = cur_seed_num_cards;
                best_seed = cur_seed;
                best_seed_index = rng_primary->index - 1;
            }

            if (cur_seed_num_cards != 0) {
                reset_good_card_bool_array(good_card_bool_array);
            }
        }
    }

    rng_init(rng_primary, best_seed);
    for (int i = 622; i < 624; i++) {
        printf("%08x, ", rng_primary->state[i]);
    }
    rng_twist(rng_primary);
    printf("\n");

    rng_primary->index = best_seed_index;
    uint rng_trader_seed = rng_next(rng_primary);
    rng_init(rng_trader, rng_trader_seed);
    printf("seed: %08x, seed diff: %d, index: %d, index in RAM: %04x, last index on title screen: %04x, rng_trader_seed: %08x, num_cards: %d\n",
             best_seed, best_seed - MACADDR_U32, best_seed_index, best_seed_index + 1, best_seed_index + 1 - 0x9f, rng_trader_seed, best_seed_num_cards);
    for (rng_index = 0; rng_index < NUM_TRADER_ATTEMPTS; rng_index++) {
        card_type card = simulate_card_trader_roll(rng_trader, card_list_list);
        printf("%s, ", card_names[card]);
    }
    printf("\n");
    
    rng_init(rng_primary, best_seed);
    rng_twist(rng_primary);
    rng_primary->index = best_seed_index + 1;
    get_auto_favourite_cards(rng_primary, slot_indices);

    printf("Slot indices (one-indexed): ");
    for (int i = 0; i < 6; i++) {
        printf("%d, ", slot_indices[i] + 1);
    }
    printf("\n");
}

void check_0xffffffff_output(void) {
    uint seed;

    for (ulong orig_seed = 0; orig_seed <= 0xffffffff; orig_seed++) {
        seed = orig_seed;
        seed ^= (seed >> 11);
        seed ^= (seed <<  7) & 0x9D2C5680;
        seed ^= (seed << 15) & 0xEFC60000;
        seed ^= (seed >> 18);
        if (((seed & 0xffff) % 0xc80) == 0xc7f) {
            printf("orig_seed: %08x, seed: %08x\n", orig_seed, seed);
        }
    }
}

void shuffle_folder(card_type * folder, uint * row_lengths, RNG * rng) {
    for (int row = 0; row < 2; row++) {
        for (int cur_card = 0; cur_card < row_lengths[row]; cur_card++) {
            u8 which_row = (rng_next(rng) >> 1) % 2;
            u8 random_card_index = (rng_next(rng) >> 1) % (row_lengths[which_row]);

            card_type * temp_folder = &folder[cur_card * 2 + row];
            card_type temp_card = *temp_folder;
            *temp_folder = folder[random_card_index * 2 + which_row];
            folder[random_card_index * 2 + which_row] = temp_card;
        }
    }
}

void sf1_shuffle(card_type * old_folder, uint folder_length, RNG * rng, uint num_cards_to_output, uint initial_seed, uint print_slot) {
    card_type folder[folder_length];
    uint row_lengths[2];

    row_lengths[0] = (folder_length / 2) + (folder_length & 1);
    row_lengths[1] = folder_length / 2;

    for (int i = 0; i < row_lengths[0]; i++) {
        //printf("[%d] = [%d]\n", i * 2, i);
        folder[i * 2] = old_folder[i];
    }
    //printf("\n");

    for (int i = 0; i < row_lengths[1]; i++) {
        //printf("[%d] = [%d]\n", i * 2 + 1, i + row_lengths[0]);
        folder[i * 2 + 1] = old_folder[i + row_lengths[0]];
    }
    //printf("\n");

    for (int i = 0; i < folder_length; i++) {
        //printf("%s, ", card_names[folder[i]]);
    }
    //printf("\n\n");

    shuffle_folder(folder, row_lengths, rng);
    rng_jump_ahead(rng, 76);
    //printf("rng->index: %04x\n", rng->index);
    shuffle_folder(folder, row_lengths, rng);

    printf("%d: ", initial_seed);
    if (print_slot) {
        for (int i = 0; i < num_cards_to_output; i++) {
            printf("%d, ", folder[i] + 1);
        }
    } else {
        for (int i = 0; i < num_cards_to_output; i++) {
            printf("%s, ", card_names[folder[i]]);
        }
    }
    printf("\n");
}

void soft_reset_manipulation(card_type * folder, uint folder_length, uint start_frame_boundary, uint end_frame_boundary, uint rng_index, uint print_slot) {
    RNG * rng = rng_instantiate(FALSE);

    for (uint cur_seed = start_frame_boundary; cur_seed <= end_frame_boundary; cur_seed++) {
        uint cur_seed_start = cur_seed;

        rng_init(rng, cur_seed);
        rng_twist(rng);
        rng->index = rng_index;
        
        sf1_shuffle(folder, folder_length, rng, 6, cur_seed, print_slot);
    }
}

void gen_folder_then_do_sf1_shuffle(void) {
    uint folder_length = 30;
    card_type folder[folder_length];

    for (card_type card = 0; card < folder_length; card++) {
        folder[card] = card;
    }

    RNG * rng = rng_instantiate(FALSE);
    rng_init(rng, 0x1337);
    rng_twist(rng);

    rng->index = 0x111;

    sf1_shuffle(folder, folder_length, rng, folder_length, 0x1337, FALSE);
}

card_type car_virus_folder[] = {
    GrassStage,
    BreakSabre,
    QnOphiucaSP,
    PlasmaGun1,
    PlasmaGun1,
    PlasmaGun1,
    AirSpread,
    AirSpread,
    AirSpread,
    JumboHmmr3,
    VulcnSeed3,
    StikyRain3,
    Sword,
    Sword,
    Sword,
    WideSword,
    WideSword,
    WideSword,
    LongSword,
    LongSword,
    LongSword,
    FireRing3,
    LeoKingdmSP,
    PegasuMgcSP,
    CygnsWingSP,
    DragonSkySP,
    FlickrKck3,
    ParlyzPlus,
    Attack_10,
    Attack_10
};

void gen_folder_then_do_soft_reset_folder_manipulation(void) {
    soft_reset_manipulation(car_virus_folder, 30, 0x250, 0x280, 0x58, FALSE);
}

void gen_slot_folder_then_do_soft_reset_folder_manipulation(uint folder_length, uint start_frame_boundary, uint end_frame_boundary, uint rng_index) {
    card_type folder[folder_length];

    for (card_type card = 0; card < folder_length; card++) {
        folder[card] = card;
    }

    soft_reset_manipulation(folder, folder_length, start_frame_boundary, end_frame_boundary, rng_index, TRUE);
}

#define ENC_PERCENT(rng) (((rng_next(rng) & 0xffff) % 0xc80) / 0x20)

uint greedy_skip_n_encounters(RNG * rng, uint num_encs, uint enc_rate, uint allow_print) {
    uint successive_enc_skips = 0;
    uint num_rng_skips = 0;
    uint total_enc_skips = 0;
    uint total_rng_skip_time = 0;
    
    while (total_enc_skips < num_encs) {
        uint enc_percent = ENC_PERCENT(rng);
        if (enc_percent <= enc_rate) {
            rng_jump_ahead(rng, 5); // try auto-favouriting 6 cards
            // first try auto-favouriting 5 cards (number is 4 to account for above RNG call advancing rng index)
            /*five_auto_favourite_skips_enc = (ENC_PERCENT(rng) <= enc_rate);
            six_auto_favourite_skips_enc = */
            if (successive_enc_skips) {
                if (allow_print) {
                    printf("skipped %d encounters\n", successive_enc_skips);
                }
                total_rng_skip_time += 192; // amount of time to open the folder
                successive_enc_skips = 0;
            }
            total_rng_skip_time += 436;
            num_rng_skips++;
        } else if (num_rng_skips) {
            if (allow_print) {
                printf("skipped %d RNG values\n", num_rng_skips);
            }
            total_rng_skip_time += 263;
            num_rng_skips = 0;
        }
        if (num_rng_skips == 0) {
            successive_enc_skips++;
            total_enc_skips++;
            enc_rate++;
            if (allow_print) {
                printf("random encounter value: %d\n", enc_percent);
            }
        }
    }
    if (successive_enc_skips && allow_print) {
        printf("skipped %d encounters\n", successive_enc_skips);
    }
    if (allow_print) {
        printf("\n");
    }
    return total_rng_skip_time;
}
            
void print_one_rng_state(void) {
    RNG * rng = rng_instantiate(FALSE);
    rng_init(rng, 0x12bf0900);

    for (int i = 0; i < 0x270; i++) {
        printf("%d, ", ENC_PERCENT(rng));
    }
    printf("\n");
}

#define TRUCK_COMP_2_RESET_ENC_RATE TRUE

void print_truck_comps_rng_seed_encounter_info(uint best_seed, uint rng_start_index) {
    RNG * rng = rng_instantiate(FALSE);
    rng_init(rng, best_seed);
    rng_jump_ahead(rng, 0x14 + rng_start_index);
    greedy_skip_n_encounters(rng, 4, 10, TRUE);
    rng_jump_ahead(rng, 0x17);
    greedy_skip_n_encounters(rng, 4, 10, TRUE);
    rng_jump_ahead(rng, 0x32);
    greedy_skip_n_encounters(rng, 6, 10, TRUE);
    rng_jump_ahead(rng, 0x2d);
    greedy_skip_n_encounters(rng, 9, 10, TRUE);
    rng_jump_ahead(rng, 0x31);
    greedy_skip_n_encounters(rng, 8, 19, TRUE);
    rng_jump_ahead(rng, 0x49);
    greedy_skip_n_encounters(rng, 6, 27, TRUE);
    rng_jump_ahead(rng, 0x51);
    if (TRUCK_COMP_2_RESET_ENC_RATE) {
        greedy_skip_n_encounters(rng, 9, 33, TRUE);
        greedy_skip_n_encounters(rng, 5, 10, TRUE);
    } else {
        greedy_skip_n_encounters(rng, 15, 33, TRUE);
    }
}

void verify_last_two_words_of_rng_state(uint seed) {
    RNG * rng = rng_instantiate(FALSE);
    rng_init(rng, seed);
    for (int i = 622; i < 624; i++) {
        printf("%08x, ", rng->state[i]);
    }
    printf("\n");
}


//0x12bf5277
void get_best_seed_for_skip_truck_comps_encounters(uint mac_addr_part) {
    RNG * rng = rng_instantiate(FALSE);
    uint cur_seed = mac_addr_part + 60;
    uint best_seed = cur_seed;
    uint best_rng_start_index = 0x17;
    uint lowest_rng_skip_time = 0xffffffff;
    uint num_retwists = 0;
    for (; cur_seed <= (mac_addr_part + 86400); cur_seed++) {
        if (cur_seed == 0xa2bf8b79 || cur_seed == 0xa2bfb10b) {
            continue;
        }
        uint cur_rng_skip_time = 0;
        rng_init(rng, cur_seed);
        for (int rng_start_index = 0xb; rng_start_index < 0x57; rng_start_index += 4) {
            if (rng->twist_count != 1) {
                rng_init(rng, cur_seed);
                rng_twist(rng);
                num_retwists++;
            }
            rng->index = 0;
            rng_jump_ahead(rng, 0x14 + rng_start_index);
            cur_rng_skip_time += greedy_skip_n_encounters(rng, 4, 10, FALSE);
            rng_jump_ahead(rng, 0x17);
            cur_rng_skip_time += greedy_skip_n_encounters(rng, 4, 10, FALSE);
            rng_jump_ahead(rng, 0x32);
            cur_rng_skip_time += greedy_skip_n_encounters(rng, 6, 10, FALSE);
            rng_jump_ahead(rng, 0x2d);
            cur_rng_skip_time += greedy_skip_n_encounters(rng, 9, 10, FALSE);
            rng_jump_ahead(rng, 0x31);
            cur_rng_skip_time += greedy_skip_n_encounters(rng, 8, 19, FALSE);
            rng_jump_ahead(rng, 0x49);
            cur_rng_skip_time += greedy_skip_n_encounters(rng, 6, 27, FALSE);
            rng_jump_ahead(rng, 0x51);
            if (TRUCK_COMP_2_RESET_ENC_RATE) {
                cur_rng_skip_time += greedy_skip_n_encounters(rng, 9, 33, FALSE);
                cur_rng_skip_time += greedy_skip_n_encounters(rng, 5, 10, FALSE);
                cur_rng_skip_time += 477;
            } else {
                cur_rng_skip_time += greedy_skip_n_encounters(rng, 15, 33, FALSE);
            }

            if (cur_rng_skip_time < lowest_rng_skip_time) {
                lowest_rng_skip_time = cur_rng_skip_time;
                best_seed = cur_seed;
                best_rng_start_index = rng_start_index;
            }
        }
    }
    printf("best seed: 0x%08x, rng index: 0x%02x, time taken: %d\n", best_seed, best_rng_start_index, lowest_rng_skip_time);
    printf("num retwists: %d\n", num_retwists);
    print_truck_comps_rng_seed_encounter_info(best_seed, best_rng_start_index);
    verify_last_two_words_of_rng_state(best_seed);
}

void verify_enc_percent_values(uint seed) {
    RNG * rng = rng_instantiate(FALSE);
    rng_init(rng, seed);
    for (int i = 0; i < 50; i++) {
        printf("%d, ", ENC_PERCENT(rng));
    }
    printf("\n");
}
    
int main(void) {
    //gen_slot_folder_then_do_soft_reset_folder_manipulation(30, 650, 1000, 44);
    //verify_enc_percent_values(0xa2bf5137);
    //get_best_seed_for_skip_truck_comps_encounters(0xa2bf0900); // 6dbe1c00
    //verify_last_two_words_of_rng_state(0xa2bfb10b);
    //skip_truck_comps_encounters();
    //check_0xffffffff_output();
    //gen_folder_then_do_soft_reset_folder_manipulation();
    //gen_folder_then_do_sf1_shuffle();
    //check_0xffffffff_output();
    find_actual_good_trader_lists(amaken_lists);
    //find_all_periods();
    /*printf("\n");
    chip_trader_optimize = FALSE;
    find_all_periods();*/
    return 0;
}