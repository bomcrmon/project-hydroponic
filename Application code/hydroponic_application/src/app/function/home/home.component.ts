import { Component, OnInit } from '@angular/core';
import { AuthService } from 'src/app/service/auth.service';
import { environment } from 'src/environments/environment';
import { AngularFireDatabase } from '@angular/fire/compat/database';
import { LineMessageService } from 'src/app/service/line-message.service';
@Component({
  selector: 'app-home',
  templateUrl: './home.component.html',
  styleUrls: ['./home.component.css'],
})
export class HomeComponent implements OnInit {
  humidityValue: any;
  temperatureValue: any;
  pHValue: any;
  waterStateHigh: any;
  waterStateLow: any;
  pump_ph_down: any;
  pump_ph_up: any;
  pump_water_up: any;
  sprinklerfertilizers: any;
  sprinklerwater: any;

  constructor(
    private auth: AuthService,
    private db: AngularFireDatabase,
    private lineMessageService: LineMessageService
  ) {}

  async ngOnInit(): Promise<void> {
    await this.getdata();
  }

  logout() {
    this.auth.logout();
  }

  async getdata() {
    await this.auth.humidityValue().subscribe((value: any) => {
      this.humidityValue = parseFloat(value.toFixed(2));
    });
    await this.auth.temperatureValue().subscribe((value: any) => {
      this.temperatureValue = parseFloat(value.toFixed(2));
    });
    await this.auth.pHValue().subscribe((value: any) => {
      this.pHValue = parseFloat(value.toFixed(2));
    });
    await this.auth.waterStateHigh().subscribe((state: any) => {
      this.waterStateHigh = state;
    });
    await this.auth.waterStateLow().subscribe((state: any) => {
      this.waterStateLow = state;
    });
  }

  updateSwitchState(switchId: string, state: boolean) {
    const switchElement = document.getElementById(switchId) as HTMLInputElement;
    if (switchElement) {
      switchElement.checked = state;
    }
  }

  sendMessageToLine(): void {
    const message = 'Hello from Angular!';
    const userId = 'USER_ID'; // Replace with the Line user ID you want to send message to
    this.lineMessageService.sendMessage(message, userId);
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

  connectLineNotify() {
    window.location.href =
      'https://notify-bot.line.me/oauth/authorize?response_type=code&client_id=<YOUR_CLIENT_ID>&redirect_uri=<YOUR_REDIRECT_URI>&scope=notify&state=<YOUR_STATE>';
  }
}
