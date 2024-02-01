import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/service/auth.service';
import { environment } from 'src/environments/environment';
import { AngularFireDatabase } from '@angular/fire/compat/database';
@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css']
})
export class HomeComponent implements OnInit{
  humidityValue: any;
  temperatureValue:any
  pHValue:any
  fertilizersState:any
  waterState:any
  fan:any
  led:any
  pump_ph_down:any
  pump_ph_up:any
  pump_water_up:any
  sprinklerfertilizers:any
  sprinklerwater:any

  constructor(private auth:AuthService,private db: AngularFireDatabase) {
    
  }

  ngOnInit(): void {
    this.auth.humidityValue().subscribe((value: any) => {
      this.humidityValue = value;
    });
    this.auth.temperatureValue().subscribe((value: any) => {
      this.temperatureValue = value;
    });
    this.auth.pHValue().subscribe((value: any) => {
      this.pHValue = value;
    });
    this.auth.fertilizersState().subscribe((state: any) => {
      this.fertilizersState = state;
    });
    this.auth.waterState().subscribe((state: any) => {
      this.waterState = state;
    });
    const relaystate_fanRef = this.db.object('relaystate/fan').valueChanges();
    relaystate_fanRef.subscribe((state: any) => {
      this.updateSwitchState('fanSwitch', state);
    });

    const relaystate_ledRef = this.db.object('relaystate/led').valueChanges();
    relaystate_ledRef.subscribe((state: any) => {
      this.updateSwitchState('ledSwitch', state);
    });

  }


  logout(){
  this.auth.logout();
  }


  updateSwitchState(switchId: string, state: boolean) {
    const switchElement = document.getElementById(switchId) as HTMLInputElement;
    if (switchElement) {
      switchElement.checked = state;
    }
  }

  fanSwitch(event: any) {
    this.db.object('relaystate/fan').set(event.target.checked);
  }

  ledSwitch(event: any) {
    this.db.object('relaystate/led').set(event.target.checked);
  }
  fertilizers(event: any) {
    this.db.object('relaystate/fertilizers').set(event.target.checked);
  }
  microbial(event: any) {
    this.db.object('relaystate/microbial').set(event.target.checked);
  }
  pumpStirring(event: any) {
    this.db.object('relaystate/pumpStirring').set(event.target.checked);
  }
  pumpUP(event: any) {
    this.db.object('relaystate/pumpUP').set(event.target.checked);
  }
  pumpphDown(event: any) {
    this.db.object('relaystate/pumpphDown').set(event.target.checked);
  }
  pumpphUP(event: any) {
    this.db.object('relaystate/pumpphUP').set(event.target.checked);
  }
  pumpwater(event: any) {
    this.db.object('relaystate/pumpwater').set(event.target.checked);
  }
  sprinkler_fertilizers(event: any) {
    this.db.object('relaystate/sprinklerfertilizers').set(event.target.checked);
  }
  sprinkler_water(event: any) {
    this.db.object('relaystate/sprinklerwater').set(event.target.checked);
  }
  valve(event: any) {
    this.db.object('relaystate/valve').set(event.target.checked);
  }



}
