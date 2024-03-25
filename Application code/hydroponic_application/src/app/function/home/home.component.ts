import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/service/auth.service';
import { environment } from 'src/environments/environment';
import { AngularFireDatabase } from '@angular/fire/compat/database';
@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css'],
})
export class HomeComponent implements OnInit {
  humidityValue: any;
  temperatureValue: any;
  pHValue: any;
  fertilizersState: any;
  waterState: any;
  pump_ph_down: any;
  pump_ph_up: any;
  pump_water_up: any;
  sprinklerfertilizers: any;
  sprinklerwater: any;

  constructor(private auth: AuthService, private db: AngularFireDatabase) {}

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
    let fan = this.db.object('relaystate/fan').valueChanges();
    fan.subscribe((state: any) => {
      this.updateSwitchState('fan', state);
    });

    let led = this.db.object('relaystate/led').valueChanges();
    led.subscribe((state: any) => {
      this.updateSwitchState('led', state);
    });

    let fertilizers = this.db.object('relaystate/fertilizers').valueChanges();
    fertilizers.subscribe((state: any) => {
      this.updateSwitchState('fertilizers', state);
    });

    let microbial = this.db.object('relaystate/microbial').valueChanges();
    microbial.subscribe((state: any) => {
      this.updateSwitchState('microbial', state);
    });

    let pumpStirring = this.db.object('relaystate/pumpStirring').valueChanges();
    pumpStirring.subscribe((state: any) => {
      this.updateSwitchState('pumpStirring', state);
    });

    let pumpUP = this.db.object('relaystate/pumpUP').valueChanges();
    pumpUP.subscribe((state: any) => {
      this.updateSwitchState('pumpUP', state);
    });

    let pumpphDown = this.db.object('relaystate/pumpphDown').valueChanges();
    pumpphDown.subscribe((state: any) => {
      this.updateSwitchState('pumpphDown', state);
    });

    let pumpphUP = this.db.object('relaystate/pumpphUP').valueChanges();
    pumpphUP.subscribe((state: any) => {
      this.updateSwitchState('pumpphUP', state);
    });

    let pumpwater = this.db.object('relaystate/pumpwater').valueChanges();
    pumpwater.subscribe((state: any) => {
      this.updateSwitchState('pumpwater', state);
    });

    let sprinkler_fertilizers = this.db
      .object('relaystate/sprinkler_fertilizers')
      .valueChanges();
    sprinkler_fertilizers.subscribe((state: any) => {
      this.updateSwitchState('sprinkler_fertilizers', state);
    });

    let sprinkler_water = this.db
      .object('relaystate/sprinkler_water')
      .valueChanges();
    sprinkler_water.subscribe((state: any) => {
      this.updateSwitchState('sprinkler_water', state);
    });

    let valve = this.db.object('relaystate/valve').valueChanges();
    valve.subscribe((state: any) => {
      this.updateSwitchState('valve', state);
    });
  }

  logout() {
    this.auth.logout();
  }

  updateSwitchState(switchId: string, state: boolean) {
    const switchElement = document.getElementById(switchId) as HTMLInputElement;
    if (switchElement) {
      switchElement.checked = state;
    }
  }

  fan(event: any) {
    this.db.object('relaystate/fan').set(event.target.checked);
  }

  led(event: any) {
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
