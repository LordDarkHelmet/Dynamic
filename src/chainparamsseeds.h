// Copyright (c) 2016-2017 Duality Blockchain Solutions Developers
// Copyright (c) 2014-2017 The Dash Core Developers
// Copyright (c) 2009-2017 The Bitcoin Developers
// Copyright (c) 2009-2017 Satoshi Nakamoto
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DYNAMIC_CHAINPARAMSSEEDS_H
#define DYNAMIC_CHAINPARAMSSEEDS_H
/**
 * List of fixed seed nodes for the Dynamic network
 * AUTOGENERATED by contrib/seeds/generate-seeds.py
 *
 * Each line contains a 16-byte IPv6 address and a port.
 * IPv4 as well as onion addresses are wrapped inside a IPv6 address accordingly.
 */

//	Dynamic Seeds
static SeedSpec6 pnSeed6_main[] = {
	{{0x00,0x00,0x00,0x00,0xff,0xff,0x2d,0x4c,0xef,0x26}, 33300},
	{{0x00,0x00,0x00,0x00,0xff,0xff,0x2d,0x4d,0x56,0xf2}, 33300},
	{{0x00,0x00,0x00,0x00,0xff,0xff,0x2d,0x4d,0x45,0xef}, 33300},
	{{0x00,0x00,0x00,0x00,0xff,0xff,0x2d,0x20,0x5f,0xcc}, 33300},
	{{0x00,0x00,0x00,0x00,0xff,0xff,0x2d,0x4c,0x4c,0x47}, 33300},
	{{0x00,0x00,0x00,0x00,0xff,0xff,0x6c,0x3d,0xd8,0xd6}, 33300}
};

static SeedSpec6 pnSeed6_test[] = {
};

#endif // DYNAMIC_CHAINPARAMSSEEDS_H
