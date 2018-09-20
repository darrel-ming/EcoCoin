/* 
 * A runnable main program that tests the functionality of class Keccak256.
 * 
 * Bitcoin cryptography library
 * Copyright (c) Project Nayuki
 * 
 * https://www.nayuki.io/page/bitcoin-cryptography-library
 * https://github.com/nayuki/Bitcoin-Cryptography-Library
 */

#include "TestHelper.hpp"
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Keccak256.hpp"


int main() {
	struct TestCase {
		bool matches;
		const char *expectedHash;
		Bytes message;
	};
	const vector<TestCase> cases{
		// ASCII vectors
		{true, "C5D2460186F7233C927E7DB2DCC703C0E500B653CA82273B7BFAD8045D85A470", asciiBytes("")},
		{true, "4D741B6F1EB29CB2A9B9911C82F56FA8D73B04959D3D9D222895DF6C0B28AA15", asciiBytes("The quick brown fox jumps over the lazy dog")},
		{true, "578951E24EFD62A3D63A86F7CD19AAA53C898FE287D2552133220370240B572D", asciiBytes("The quick brown fox jumps over the lazy dog.")},
		// Binary vectors
		{true, "6A769F93F255B078FE73AFF68F0422A279939920E4690B4AFF0E433CFA3D3DF3", hexBytes("13BD2811F6ED2B6F04FF3895ACEED7BEF8DCD45EB121791BC194A0F806206BFFC3B9281C2B308B1A729CE008119DD3066E9378ACDCC50A98A82E20738800B6CDDBE5FE9694AD6D")},
		{true, "C06DD4261638C44AFCB186F0AF5DE20EA53AA63316FBB71728F874FF3DACEB0D", hexBytes("1EED9CBA179A009EC2EC5508773DD305477CA117E6D569E66B5F64C6BC64801CE25A8424CE4A26D575B8A6FB10EAD3FD1992EDDDEEC2EBE7150DC98F63ADC3237EF57B91397AA8A7")},
		{true, "52CBC5DBE49B009663C43F079DD180E38A77533778062A72A29E864A58522922", hexBytes("F13C972C52CB3CC4A4DF28C97F2DF11CE089B815466BE88863243EB318C2ADB1A417CB1041308598541720197B9B1CB5BA2318BD5574D1DF2174AF14884149BA9B2F446D609DF240CE335599957B8EC80876D9A085AE084907BC5961B20BF5F6CA58D5DAB38ADB")},
		{true, "3A8DFCFD1B362003DDFA17910727539E64B18021ABBA018B5F58D71F7A449733", hexBytes("E35780EB9799AD4C77535D4DDB683CF33EF367715327CF4C4A58ED9CBDCDD486F669F80189D549A9364FA82A51A52654EC721BB3AAB95DCEB4A86A6AFA93826DB923517E928F33E3FBA850D45660EF83B9876ACCAFA2A9987A254B137C6E140A21691E1069413848")},
		{true, "BD6F5492582A7C1B116304DE28314DF9FFFE95B0DA11AF52FE9440A717A34859", hexBytes("B771D5CEF5D1A41A93D15643D7181D2A2EF0A8E84D91812F20ED21F147BEF732BF3A60EF4067C3734B85BC8CD471780F10DC9E8291B58339A677B960218F71E793F2797AEA349406512829065D37BB55EA796FA4F56FD8896B49B2CD19B43215AD967C712B24E5032D065232E02C127409D2ED4146B9D75D763D52DB98D949D3B0FED6A8052FBB")},
		{true, "E717A7769448ABBE5FEF8187954A88AC56DED1D22E63940AB80D029585A21921", hexBytes("B32D95B0B9AAD2A8816DE6D06D1F86008505BD8C14124F6E9A163B5A2ADE55F835D0EC3880EF50700D3B25E42CC0AF050CCD1BE5E555B23087E04D7BF9813622780C7313A1954F8740B6EE2D3F71F768DD417F520482BD3A08D4F222B4EE9DBD015447B33507DD50F3AB4247C5DE9A8ABD62A8DECEA01E3B87C8B927F5B08BEB37674C6F8E380C04")},
		{true, "344D129C228359463C40555D94213D015627E5871C04F106A0FEEF9361CDECB6", hexBytes("EA40E83CB18B3A242C1ECC6CCD0B7853A439DAB2C569CFC6DC38A19F5C90ACBF76AEF9EA3742FF3B54EF7D36EB7CE4FF1C9AB3BC119CFF6BE93C03E208783335C0AB8137BE5B10CDC66FF3F89A1BDDC6A1EED74F504CBE7290690BB295A872B9E3FE2CEE9E6C67C41DB8EFD7D863CF10F840FE618E7936DA3DCA5CA6DF933F24F6954BA0801A1294CD8D7E66DFAFEC")},
		{true, "4CE7C2B935F21FC34C5E56D940A555C593872AEC2F896DE4E68F2A017060F535", hexBytes("157D5B7E4507F66D9A267476D33831E7BB768D4D04CC3438DA12F9010263EA5FCAFBDE2579DB2F6B58F911D593D5F79FB05FE3596E3FA80FF2F761D1B0E57080055C118C53E53CDB63055261D7C9B2B39BD90ACC32520CBBDBDA2C4FD8856DBCEE173132A2679198DAF83007A9B5C51511AE49766C792A29520388444EBEFE28256FB33D4260439CBA73A9479EE00C63")},
		// secp256k1 curve point public key vectors
		{true, "72F15D6555488541650CE62C0BED7ABD61247635C1973EB38474A2516ED1D884", hexBytes("836B35A026743E823A90A0EE3B91BF615C6A757E2B60B9E1DC1826FD0DD16106F7BC1E8179F665015F43C6C81F39062FC2086ED849625C06E04697698B21855E")},
		{true, "500625E5A55B726C0FC56C62C2D7CF95645D33006175B78989035C7C9061D3F9", hexBytes("EFB99D9860F4DEC4CB548A5722C27E9EF58E37FBAB9719C5B33D55C216DB49311221A01F638CE5F255875B194E0ACAA58B19A89D2E56A864427298F826A7F887")},
		{true, "6F68D681DE0407D447C30E14DD4ECCD742D17887F50C27AEBB14D99BFD7571B6", hexBytes("C5BC5C47FFA548D0F2B63D4F05FA7064D72FA3657C287F38CC87140A639C9465D4C9EDEC42F06B631C443311FD91585BCAB873136EAC50AF6DAA5363F0405544")},
	};
	
	int numTestCases = 0;
	for (const TestCase &tc : cases) {
		Bytes expectHash = hexBytes(tc.expectedHash);
		assert(expectHash.size() == Keccak256::HASH_LEN);
		std::uint8_t actualHash[Keccak256::HASH_LEN];
		Keccak256::getHash(tc.message.data(), tc.message.size(), actualHash);
		assert((std::memcmp(actualHash, expectHash.data(), Keccak256::HASH_LEN) == 0) == tc.matches);
		numTestCases++;
	}
	std::printf("All %d test cases passed\n", numTestCases);
	return EXIT_SUCCESS;
}
