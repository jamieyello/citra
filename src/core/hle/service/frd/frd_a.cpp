// Copyright 2015 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "core/hle/service/frd/frd.h"
#include "core/hle/service/frd/frd_a.h"

namespace Service {
namespace FRD {

const Interface::FunctionInfo FunctionTable[] = {
    {0x00010000, HasLoggedIn, "HasLoggedIn"},
    {0x00020000, IsOnline, "IsOnline"},
    {0x00030002, Login, "Login"},
    {0x00040000, Logout, "Logout"},
    {0x00050000, GetMyFriendKey, "GetMyFriendKey"},
    {0x00060000, GetMyPreference, "GetMyPreference"},
    {0x00070000, GetMyProfile, "GetMyProfile"},
    {0x00080000, GetMyPresence, "GetMyPresence"},
    {0x00090000, GetMyScreenName, "GetMyScreenName"},
    {0x000A0000, GetMyMii, "GetMyMii"},
    {0x000B0000, nullptr, "GetMyLocalAccountId"},
    {0x000C0000, GetMyPlayingGame, "GetMyPlayingGame"},
    {0x000D0000, GetMyFavoriteGame, "GetMyFavoriteGame"},
    {0x000E0000, nullptr, "GetMyNcPrincipalId"},
    {0x000F0000, GetMyComment, "GetMyComment"},
    {0x00100040, nullptr, "GetMyPassword"},
    {0x00110080, GetFriendKeyList, "GetFriendKeyList"},
    {0x00120042, nullptr, "GetFriendPresence"},
    {0x00130142, nullptr, "GetFriendScreenName"},
    {0x00140044, nullptr, "GetFriendMii"},
    {0x00150042, GetFriendProfile, "GetFriendProfile"},
    {0x00160042, GetFriendRelationship, "GetFriendRelationship"},
    {0x00170042, GetFriendAttributeFlags, "GetFriendAttributeFlags"},
    {0x00180044, nullptr, "GetFriendPlayingGame"},
    {0x00190042, nullptr, "GetFriendFavoriteGame"},
    {0x001A00C4, nullptr, "GetFriendInfo"},
    {0x001B0080, nullptr, "IsIncludedInFriendList"},
    {0x001C0042, nullptr, "UnscrambleLocalFriendCode"},
    {0x001D0002, UpdateGameModeDescription, "UpdateGameModeDescription"},
    {0x001E02C2, nullptr, "UpdateGameMode"},
    {0x001F0042, nullptr, "SendInvitation"},
    {0x00200002, AttachToEventNotification, "AttachToEventNotification"},
    {0x00210040, SetNotificationMask, "SetNotificationMask"},
    {0x00220040, nullptr, "GetEventNotification"},
    {0x00230000, GetLastResponseResult, "GetLastResponseResult"},
    {0x00240040, PrincipalIdToFriendCode, "PrincipalIdToFriendCode"},
    {0x00250080, nullptr, "FriendCodeToPrincipalId"},
    {0x00260080, nullptr, "IsValidFriendCode"},
    {0x00270040, ResultToErrorCode, "ResultToErrorCode"},
    {0x00280244, RequestGameAuthentication, "RequestGameAuthentication"},
    {0x00290000, GetGameAuthenticationData, "GetGameAuthenticationData"},
    {0x002A0204, nullptr, "RequestServiceLocator"},
    {0x002B0000, nullptr, "GetServiceLocatorData"},
    {0x002C0002, nullptr, "DetectNatProperties"},
    {0x002D0000, nullptr, "GetNatProperties"},
    {0x002E0000, nullptr, "GetServerTimeInterval"},
    {0x002F0040, nullptr, "AllowHalfAwake"},
    {0x00300000, nullptr, "GetServerTypes"},
    {0x00310082, nullptr, "GetFriendComment"},
    {0x00320042, nullptr, "SetClientSdkVersion"},
    {0x00330000, nullptr, "GetMyApproachContext"},
    {0x00340046, nullptr, "AddFriendWithApproach"},
    {0x00350082, nullptr, "DecryptApproachContext"},
    {0x04030040, nullptr, "LoadLocalAccount"},
    {0x04050000, nullptr, "Save"},
    {0x04060042, nullptr, "AddFriendOnline"},
    {0x04070D80, AddOrUpdateFriend, "AddOrUpdateFriend"},
    {0x04090100, RemoveFriend, "RemoveFriend"},
    {0x040B00C0, nullptr, "UpdatePreference"},
    {0x040F0240, nullptr, "UpdateComment"},

};

FRD_A_Interface::FRD_A_Interface() {
    Register(FunctionTable);
}

} // namespace FRD
} // namespace Service
