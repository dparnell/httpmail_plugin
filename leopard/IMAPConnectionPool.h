/*
 *     Generated by class-dump 3.1.
 *
 *     class-dump is Copyright (C) 1997-1998, 2000-2001, 2004-2005 by Steve Nygard.
 */

#import "NSObject.h"

@class NSCondition, NSMutableArray, NSMutableDictionary;

@interface IMAPConnectionPool : NSObject
{
    NSMutableDictionary *_idleConnectionsByMailbox;
    NSMutableDictionary *_activeConnectionsByMailbox;
    NSMutableArray *_suspendedGateways;
    unsigned int _maximumConnectionCount;
    NSCondition *_availabilityCondition;
}

- (void)dealloc;
- (void)_removeAllConnectionsInDictionary:(id)fp8;
- (void)_sealSuspendedGateways;
- (id)init;
- (unsigned int)connectionCount;
- (void)removeInvalidConnections;
- (void)_removeInvalidConnectionsInDictionary:(id)fp8;
- (void)closeAllConnectionsAndCompact:(BOOL)fp8;
- (void)_closeAllConnectionsAndCompact:(BOOL)fp8 inDictionary:(id)fp12;
- (BOOL)checkInConnection:(id)fp8 forGateway:(id)fp12;
- (void)checkInNewConnection:(id)fp8;
- (void)observeValueForKeyPath:(id)fp8 ofObject:(id)fp12 change:(id)fp16 context:(void *)fp20;
- (void)_removeDisconnectedConnection:(id)fp8 shouldRecover:(BOOL)fp12;
- (id)checkOutNewGatewayWithConnection:(id)fp8;
- (id)_checkOutNewGatewayWithConnection:(id)fp8 forMailbox:(id)fp12;
- (id)checkOutGatewayForMailbox:(id)fp8;
- (id)checkOutGatewayForExistingConnectionToMailbox:(id)fp8;
- (id)checkOutGatewayForMailbox:(id)fp8 newConnection:(id)fp12 highPriority:(BOOL)fp16 waitIndefinitely:(BOOL)fp20;
- (BOOL)tryToResumeGateway:(id)fp8;
- (void)sealGatewayShutIfNoChanceOfResuming:(id)fp8;
- (BOOL)yieldGateway:(id)fp8;
- (BOOL)suspendGateway:(id)fp8 withOperation:(id)fp12;
- (id)_suspendGatewayOfConnection:(id)fp8 mailbox:(id)fp12 forMailbox:(id)fp16 resumingGateway:(id)fp20;
- (id)_suspendFirstIdleConnectionForMailbox:(id)fp8 resumingGateway:(id)fp12 totalSecondsWaited:(unsigned int *)fp16 mightBeSuccessful:(char *)fp20;
- (id)_suspendFirstIdleConnectionInIdleConnections:(id)fp8 forMailbox:(id)fp12 resumingGateway:(id)fp16;
- (id)_anyConnectionFromDictionary:(id)fp8 selectedOnly:(BOOL)fp12 mailbox:(id *)fp16;
- (id)_gatewayToCheckOutConnection:(id)fp8 defaultGateway:(id)fp12 mailboxName:(id)fp16 newGateway:(char *)fp20;
- (BOOL)_validateAndCheckOutGateway:(id)fp8 forMailbox:(id)fp12 allowReconnect:(BOOL)fp16 newGateway:(BOOL)fp20;
- (id)_createNewGatewayForConnection:(id)fp8 mailboxName:(id)fp12;
- (void)_makeConnectionAvailable:(id)fp8;
- (id)description;
- (void)updateConnectionsShouldUseIdle:(id)fp8;
- (BOOL)_removeConnection:(id)fp8 fromDictionary:(id)fp12;
- (void)_setConnection:(id)fp8 forMailbox:(id)fp12 clear:(BOOL)fp16 inDictionary:(id)fp20;
- (BOOL)_connectionIsContained:(id)fp8 forMailbox:(id)fp12 inDictionary:(id)fp16;
- (id)_suspendedGatewayForMailbox:(id)fp8;
- (id)_suspendedGatewayWithWorkRequireSelected:(BOOL)fp8;
- (void)_suspendGateway:(id)fp8 allowNetworking:(BOOL)fp12;
- (void)_removeSuspendedGateway:(id)fp8;
- (id)_keyForMailboxName:(id)fp8;
- (id)connections;
- (id)suspendedGateways;
- (void)setSuspendedGateways:(id)fp8;
- (id)activeConnectionsByMailbox;
- (void)setActiveConnectionsByMailbox:(id)fp8;
- (id)idleConnectionsByMailbox;
- (void)setIdleConnectionsByMailbox:(id)fp8;
- (id)availabilityCondition;
- (void)setAvailabilityCondition:(id)fp8;
- (unsigned int)maximumConnectionCount;
- (void)setMaximumConnectionCount:(unsigned int)fp8;

@end

