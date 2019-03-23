
# Commands executed after link establish

# Start link test
#iwpriv ath1 kwn_tput_dur 2
#iwpriv ath1 kwn_tput_cnt 1
#iwpriv ath1 kwn_tput_size 1400
#iwpriv ath1 kwn_tput_dir 3
#iwpriv ath1 kwn_tput_test 1

# Commands executing for TXBA SETUP
iwpriv ath1 kwn_tput_size 1400
iwpriv ath1 kwn_tput_cnt 10
iwpriv ath1 kwntxbasetup 1

# Remove backup files for link inactivity and wireless inactivity
rm -rf /tmp/.tx_wifipkt_cur 
rm -rf /tmp/.tx_wifipkt_backup
rm -rf /tmp/.link_cur 
rm -rf /tmp/.link_backup
